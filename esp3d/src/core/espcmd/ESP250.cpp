/*
 ESP250.cpp - ESP3D command class

 Copyright (c) 2014 Luc Lebosse. All rights reserved.

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with This code; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "../../include/esp3d_config.h"
#if defined(BUZZER_DEVICE)
#include "../../modules/authentication/authentication_service.h"
#include "../../modules/buzzer/buzzer.h"
#include "../esp3d_commands.h"
#include "../esp3d_message.h"
#include "../esp3d_settings.h"

#define COMMANDID 250
// Play sound
//[ESP250]F=<frequency> D=<duration> json=<no> [pwd=<user password>]
bool Commands::ESP250(const char* cmd_params,
                      ESP3DAuthenticationLevel auth_type,
                      ESP3D_Message* esp3dmsg) {
  bool noError = true;
  bool json = has_tag(cmd_params, "json");
  String response;
  String parameter;
  int errorCode = 200;  // unless it is a server error use 200 as default and
                        // set error in json instead
#ifdef AUTHENTICATION_FEATURE
  if (auth_type == guest) {
    response = format_response(COMMANDID, json, false,
                               "Guest user can't use this command");
    noError = false;
    errorCode = 401;
  }
#else
  (void)auth_type;
#endif  // AUTHENTICATION_FEATURE
  if (noError) {
    if (!esp3d_buzzer.started()) {
      response = format_response(COMMANDID, json, false, "Buzzer disabled");
      noError = false;
    } else {
      parameter = get_param(cmd_params, "");
      // get
      if (parameter.length() == 0) {
        esp3d_buzzer.beep();
      } else {
        int f, d;
        // frequency
        parameter = get_param(cmd_params, "F=");
        if (parameter.length() == 0) {
          response = format_response(COMMANDID, json, false, "No frequency");
          noError = false;
        } else {
          f = parameter.toInt();
          parameter = get_param(cmd_params, "D=");
          if (parameter.length() == 0) {
            response = format_response(COMMANDID, json, false, "No duration");
            noError = false;
          } else {
            d = parameter.toInt();
            esp3d_buzzer.beep(f, d);
          }
        }
      }
      if (noError) {
        response = format_response(COMMANDID, json, true, "ok");
      }
    }
  }
  if (json) {
    esp3dmsg->printLN(response.c_str());
  } else {
    if (noError) {
      esp3dmsg->printMSG(response.c_str());
    } else {
      esp3dmsg->printERROR(response.c_str(), errorCode);
    }
  }
  return noError;
}

#endif  // BUZZER_DEVICE
