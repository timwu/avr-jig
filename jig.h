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
#ifndef __JIG_H__
#define __JIG_H__

char PROGMEM usbDescriptorDevice[] = {
	0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
	0x4c, 0x05, 0xeb, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01,
};

char PROGMEM usbDescriptorConfiguration[] = {
	// config
	0x09, 0x02, 0x20, 0x00, 0x01, 0x00, 0x00, 0x80,
	0x01,
	// interface
	0x09, 0x04, 0x00, 0x00, 0x02, 0xff, 0x00, 0x00,
	0x00,
	// endpoint
	0x07, 0x05, 0x02, 0x02, 0x08, 0x00, 0x00,
	// endpoint
	0x07, 0x05, 0x81, 0x02, 0x08, 0x00, 0x00,
};

#endif // __JIG_H__
