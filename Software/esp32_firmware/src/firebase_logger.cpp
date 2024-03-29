// Copyright 2023 Myron Rodrigues
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "firebase_logger.h"

//Provide the token generation process info.
#include "addons/RTDBHelper.h"
#include "addons/TokenHelper.h"

void FireLogger::print_error()
{
  Serial.printf("Error:\ncode: %d\nmsg: ", fbdo_.errorCode());
  Serial.printf("HTTP code: %d\n", fbdo_.httpCode());
  Serial.printf(
    "Firebase http connected: %s\n", fbdo_.httpConnected() ? "true" : "false");
  Serial.println(fbdo_.errorReason());
}

bool FireLogger::is_keep_alive() { return fbdo_.isKeepAlive(); }

bool FireLogger::is_connected() { return fbdo_.httpConnected(); }

FireLogger::FireLogger() : path_prefix_("/users/") {}

void FireLogger::begin(
  const char * fire_url, const char * fire_token, const char * email,
  const char * pass)
{
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected ...");
    delay(1000);
  }
  Serial.print("WiFi connected at IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Signing up to Firebase");

  config_.database_url = fire_url;
  config_.api_key = fire_token;
  auth_.user.email = email;
  auth_.user.password = pass;

  fbdo_.setResponseSize(4096);

  /* Assign the callback function for the long running token generation task */
  config_.token_status_callback =
    tokenStatusCallback;  // see addons/TokenHelper.h
  // Assign the maximum retry of token generation
  config_.max_token_generation_retry = 5;

  Firebase.begin(&config_, &auth_);
  // Getting the user UID might take a few seconds
  Serial.println("Getting User ID");
  while ((auth_.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("Got User ID");
  path_prefix_ += auth_.token.uid.c_str();
  path_prefix_ += "/";
}

MB_String FireLogger::full_path(const char * path)
{
  MB_String temp = path_prefix_.c_str();
  return temp += path;
}

void FireLogger::set_int(const char * path, int64_t value)
{
  if (!Firebase.RTDB.setInt(&fbdo_, full_path(path), value)) {
    print_error();
  }
}

void FireLogger::set_float(const char * path, double value)
{
  if (!Firebase.RTDB.setDouble(&fbdo_, full_path(path), value)) {
    print_error();
  }
}

void FireLogger::set_string(const char * path, const char * value)
{
  if (!Firebase.RTDB.setString(&fbdo_, full_path(path), value)) {
    print_error();
  }
}

void FireLogger::set_bool(const char * path, bool value)
{
  if (!Firebase.RTDB.setBool(&fbdo_, full_path(path), value)) {
    print_error();
  }
}

void FireLogger::push_time(const char * path, time_t timestamp)
{
  if (!Firebase.RTDB.pushInt(&fbdo_, full_path(path), timestamp)) {
    print_error();
  }
}

bool FireLogger::is_ready() { return Firebase.ready(); }

bool FireLogger::check_and_refresh_token()
{
  if (Firebase.isTokenExpired()) {
    Firebase.refreshToken(&config_);
    Serial.println("Refreshed token");
    return true;
  }
  return false;
}