# Copyright 2012 Eric A Wollesen
#
# This program is distributed the terms of the GNU General Public License.
#
#
# This file is part of mbp-fn-flip.
#
# mbp-fn-flip is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# mbp-fn-flip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with mbp-fn-flip.  If not, see <http://www.gnu.org/licenses/>.

all: mbp-fn-flip

mbp-fn-flip: mbp-fn-flip.o
	gcc -o mbp-fn-flip mbp-fn-flip.o

clean:
	rm -f *.o mbp-fn-flip

install: mbp-fn-flip
	install -g root -o root -m 4755 ./mbp-fn-flip /usr/local/bin/mbp-fn-flip
