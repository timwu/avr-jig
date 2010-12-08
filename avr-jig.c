/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>

#include "hmac.h"
#include "jig.h"
#include "oddebug.h"
#include "usbdrv.h"

static uchar challenge[64];
static uchar rxdChallengeBytes = 0;
static uchar challenged = 0;
static uchar response[64];
static uchar txdResponseBytes = 0;
static uchar responseReady = 0;

uchar usbFunctionWrite(uchar *data, uchar len)
{
   memcpy(challenge + rxdChallengeBytes, data, len);
   rxdChallengeBytes += len;
   challenged = rxdChallengeBytes >= sizeof(challenge);
   return !challenged;
}

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
   return 0; // just ignore any non-standard setup reqs for now
}

void sendResponse(void)
{
   if (usbInterruptIsReady()) {
      if (txdResponseBytes >= sizeof(response)) {
         responseReady = 0;
         DBGMSG1("Response sent. All done!");
         return;
      }
      uchar sendBytes = sizeof(response) - txdResponseBytes > 8 ? 
                           8 : 
                           sizeof(response) - txdResponseBytes;
      usbSetInterrupt(response + txdResponseBytes, sendBytes);
      txdResponseBytes += sendBytes;
   }
}

void formResponse(void)
{
   DBGX1("Challenge: ", challenge, sizeof(challenge));
   memcpy_P(response, responseHeader, sizeof(responseHeader));
   HMACOnce(usbDongleKey, sizeof(usbDongleKey),
            challenge + CHALLENGE_OFFSET, sizeof(shadigest));
   memcpy(response + RESPONSE_OFFSET, shadigest, sizeof(shadigest));
   DBGX1("Response: ", response, sizeof(response));
   responseReady = 1;
   challenged = 0;
}

int main(void)
{
   // Startup
   odDebugInit();
   usbDeviceConnect();
   usbInit();
   sei();

   DBGMSG1("Ready.");
   for(;;) {
      usbPoll();
      if (challenged) formResponse();
      if (responseReady) sendResponse();
   }
}

