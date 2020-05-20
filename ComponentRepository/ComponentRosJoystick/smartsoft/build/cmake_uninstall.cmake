# --------------------------------------------------------------------------
#
#  Copyright (C) 2013 Alex Lotz
#
#        lotz@fh-ulm.de
#
#        Alex Lotz
#        University of Applied Sciences
#        Prittwitzstr. 10
#        D-89075 Ulm
#        Germany
#
#  This file is part of the "SmartSoft Communication Library".
#  It provides standardized patterns for communication between
#  different components.
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# --------------------------------------------------------------------------

IF(NOT EXISTS "/home/uwrosys/SOFTWARE/uwrosys/ComponentRepository/ComponentRosJoystick/smartsoft/build/install_manifest.txt")
    MESSAGE("Cannot find install manifest: \"/home/uwrosys/SOFTWARE/uwrosys/ComponentRepository/ComponentRosJoystick/smartsoft/build/install_manifest.txt\"")
ELSE(NOT EXISTS "/home/uwrosys/SOFTWARE/uwrosys/ComponentRepository/ComponentRosJoystick/smartsoft/build/install_manifest.txt")
FILE(READ "/home/uwrosys/SOFTWARE/uwrosys/ComponentRepository/ComponentRosJoystick/smartsoft/build/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
# LIST(REVERSE files)
FOREACH (file ${files})
    MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    IF (EXISTS "$ENV{DESTDIR}${file}")
        EXECUTE_PROCESS(
            COMMAND /usr/bin/cmake -E remove "$ENV{DESTDIR}${file}"
            OUTPUT_VARIABLE rm_out
            RESULT_VARIABLE rm_retval
        )
        IF (NOT ${rm_retval} EQUAL 0)
            MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
        ENDIF (NOT ${rm_retval} EQUAL 0)
    ELSE (EXISTS "$ENV{DESTDIR}${file}")
        MESSAGE(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
    ENDIF (EXISTS "$ENV{DESTDIR}${file}")
ENDFOREACH(file)

ENDIF(NOT EXISTS "/home/uwrosys/SOFTWARE/uwrosys/ComponentRepository/ComponentRosJoystick/smartsoft/build/install_manifest.txt")
