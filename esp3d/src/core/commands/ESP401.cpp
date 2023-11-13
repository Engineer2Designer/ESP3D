/*
 ESP401.cpp - ESP3D command class

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
#include "../../modules/authentication/authentication_service.h"
#include "../esp3d_commands.h"
#include "../esp3d_message.h"
#include "../esp3d_settings.h"

#define COMMANDID 401
#if COMMUNICATION_PROTOCOL != SOCKET_SERIAL || defined(ESP_SERIAL_BRIDGE_OUTPUT)
#include "../../modules/serial/serial_service.h"
#endif  // COMMUNICATION_PROTOCOL != SOCKET_SERIAL
#ifdef SENSOR_DEVICE
#include "../../modules/sensor/sensor.h"
#endif  // SENSOR_DEVICE
#ifdef BUZZER_DEVICE
#include "../../modules/buzzer/buzzer.h"
#endif  // BUZZER_DEVICE
#ifdef TIMESTAMP_FEATURE
#include "../../modules/time/time_service.h"
#endif  // TIMESTAMP_FEATURE
#ifdef NOTIFICATION_FEATURE
#include "../../modules/notifications/notifications_service.h"
#endif  // NOTIFICATION_FEATURE
#ifdef SD_DEVICE
#include "../../modules/filesystem/esp_sd.h"
#endif  // SD_DEVICE
// Set EEPROM setting
//[ESP401]P=<position> T=<type> V=<value> json=<no> pwd=<user/admin password>
void ESP3DCommands::ESP401(int cmd_params_pos, ESP3DMessage* msg) {
  /*
  bool noError = true;
  bool json = has_tag(cmd_params, "json");
  String spos = "";
  String response;
  String parameter;
  int errorCode = 200;  // unless it is a server error use 200 as default and
                        // set error in json instead
#ifdef AUTHENTICATION_FEATURE
  if (auth_type != admin) {
    response = "Wrong authentication level";
    noError = false;
    errorCode = 401;
  }
#else
  (void)auth_type;
#endif  // AUTHENTICATION_FEATURE
  if (noError) {
    // check validity of parameters
    spos = get_param(cmd_params, "P=");
    String styp = get_param(cmd_params, "T=");
    String sval = get_param(cmd_params, "V=");
    if (spos.length() == 0) {
      response = "Invalid parameter P";
      noError = false;
    } else if (styp.length() == 0) {
      response = "Invalid parameter T";
      noError = false;
    } else if (sval.length() == 0 && !strstr(cmd_params, "V=")) {
      response = "Invalid parameter V";
      noError = false;
    } else {
      if (!(styp == "B" || styp == "S" || styp == "A" || styp == "I")) {
        response = "Invalid value for T";
        noError = false;
      }
    }
    if (noError) {
      if (response) {
        // Byte value
        if (styp == "B") {
          if (ESP3DSettings::isValidByteSetting((uint8_t)sval.toInt(),
                                                spos.toInt())) {
            if (!ESP3DSettings::writeByte(spos.toInt(),
                                           (uint8_t)sval.toInt())) {
              response = false;
              esp3d_log_e("Set failed");
            } else {
              // dynamique refresh is better than restart the boards
              switch (spos.toInt()) {
#if defined(ESP_SERIAL_BRIDGE_OUTPUT)
                case ESP_SERIAL_BRIDGE_ON:
                  if (!serial_bridge_service.started()) {
                    serial_bridge_service.begin(ESP_SERIAL_BRIDGE_OUTPUT);
                  }
                  break;
#endif  // ESP_SERIAL_BRIDGE_OUTPUT
                case ESP_VERBOSE_BOOT:
                  ESP3DSettings::isVerboseBoot(true);
                  break;
                case ESP_TARGET_FW:
                  ESP3DSettings::GetFirmwareTarget(true);
                  break;
#if COMMUNICATION_PROTOCOL == RAW_SERIAL || COMMUNICATION_PROTOCOL == MKS_SERIAL
                case ESP_SECURE_SERIAL:
                  esp3d_serial_service.setParameters();
                  break;
#endif  // COMMUNICATION_PROTOCOL == RAW_SERIAL || COMMUNICATION_PROTOCOL ==
        // MKS_SERIAL
#ifdef AUTHENTICATION_FEATURE
                case ESP_SESSION_TIMEOUT:
                  AuthenticationService::setSessionTimeout(1000 * 60 *
                                                           sval.toInt());
                  break;
#endif  // AUTHENTICATION_FEATURE
#ifdef SD_DEVICE
                case ESP_SD_SPEED_DIV:
                  ESP_SD::setSPISpeedDivider(sval.toInt());
                  break;
#endif  // SD_DEVICE
#ifdef TIMESTAMP_FEATURE
                case ESP_INTERNET_TIME:
                  timeService.begin();
                  break;
#endif  // TIMESTAMP_FEATURE
#ifdef NOTIFICATION_FEATURE
                case ESP_AUTO_NOTIFICATION:
                  notificationsservice.setAutonotification(
                      (sval.toInt() == 0) ? false : true);
                  break;
#endif  // NOTIFICATION_FEATURE
#ifdef SENSOR_DEVICE
                case ESP_SENSOR_TYPE:
                  esp3d_sensor.begin();
                  break;
#endif  // SENSOR_DEVICE
#ifdef BUZZER_DEVICE
                case ESP_BUZZER:
                  if (sval.toInt() == 1) {
                    esp3d_buzzer.begin();
                  } else if (sval.toInt() == 0) {
                    esp3d_buzzer.end();
                  }
                  break;
#endif  // BUZZER_DEVICE
                default:
                  break;
              }
            }
          } else {
            response = "Invalid value for V";
            noError = false;
          }
        }
        // Integer value
        if (styp == "I") {
          if (ESP3DSettings::isValidByteSetting(sval.toInt(), spos.toInt())) {
            if (!ESP3DSettings::writeUint32(spos.toInt(), sval.toInt())) {
              response = "Set failed";
              noError = false;
              esp3d_log_e("Set failed");
            } else {
              // dynamique refresh is better than restart the board
              switch (spos.toInt()) {
#ifdef SENSOR_DEVICE
                case ESP_SENSOR_INTERVAL:
                  esp3d_sensor.setInterval(sval.toInt());
                  break;
#endif  // SENSOR_DEVICE
#if COMMUNICATION_PROTOCOL == RAW_SERIAL || COMMUNICATION_PROTOCOL == MKS_SERIAL
                case ESP_BAUD_RATE:
                  esp3d_serial_service.updateBaudRate(sval.toInt());
                  break;
#endif  // COMMUNICATION_PROTOCOL == RAW_SERIAL || COMMUNICATION_PROTOCOL ==
        // MKS_SERIAL
#if defined(ESP_SERIAL_BRIDGE_OUTPUT)
                case ESP_SERIAL_BRIDGE_BAUD:
                  serial_bridge_service.updateBaudRate(sval.toInt());
                  break;
#endif  // defined(ESP_SERIAL_BRIDGE_OUTPUT)
                default:
                  break;
              }
            }
          } else {
            response = "Invalid value for V";
            noError = false;
          }
        }
        // String value
        if (styp == "S") {
          if (ESP3DSettings::isValidStringSetting(sval.c_str(), spos.toInt())) {
            if (!ESP3DSettings::writeStringspos.toInt(), sval.c_str())) {
              response = "Set failed";
              noError = false;
              esp3d_log_e("Set failed");
            } else {
              // dynamique refresh is better than restart the board
              switch (spos.toInt()) {
#ifdef AUTHENTICATION_FEATURE
                case ESP_ADMIN_PWD:
                case ESP_USER_PWD:
                  AuthenticationService::update();
                  break;
#endif  // AUTHENTICATION_FEATURE
                default:
                  break;
              }
            }
          } else {
            response = "Invalid value for V";
            noError = false;
          }
        }
#if defined(WIFI_FEATURE)
        // IP address
        if (styp == "A") {
          if (ESP3DSettings::isValidIPStringSetting(sval.c_str(),
                                                    spos.toInt())) {
            if (!ESP3DSettings::writeIPString(spos.toInt(), sval.c_str())) {
              response = "Set failed";
              noError = false;
            } else {
              // dynamique refresh is better than restart the board
              // TBD
            }
          } else {
            response = "Invalid value for V";
            noError = false;
          }
        }
#endif  // WIFI_FEATURE
      }
    }
  }
  if (noError) {
    if (json) {
      response = format_response(COMMANDID, json, true, String(spos).c_str());
      esp3dmsg->printLN(response.c_str());
    } else {
      response = format_response(COMMANDID, json, true, "ok");
      esp3dmsg->printMSG(response.c_str());
    }
  } else {
    if (json) {
      String tmp = "{\"error\":\"";
      tmp += response;
      tmp += "\"";
      if (spos.length() > 0) {
        tmp += ",\"position\":\"";
        tmp += spos;
        tmp += "\"";
      }
      tmp += "}";
      response = tmp;
    } else {
      response += spos.length() > 0 ? " for P=" + spos : "";
    }
    response = format_response(COMMANDID, json, false, response.c_str());
    if (json) {
      esp3dmsg->printLN(response.c_str());
    } else {
      esp3dmsg->printERROR(response.c_str(), errorCode);
    }
  }
  return noError;*/
}
