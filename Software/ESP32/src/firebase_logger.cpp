#include "firebase_logger.h"

//Provide the token generation process info.
#include "addons/TokenHelper.h"

void FireLogger::print_error()
{
  Serial.printf("Error:\ncode: %d\nmsg: ", fbdo_.errorCode());
  Serial.println(fbdo_.errorReason());
}

FireLogger::FireLogger(
  WiFiClass * wifi, const char * fire_url, const char * fire_token,
  const char * email, const char * pass)
: wifi_(wifi), path_prefix_("/users/")
{
  config_.database_url = fire_url;
  config_.api_key = fire_token;
  auth_.user.email = email;
  auth_.user.password = pass;
}

void FireLogger::begin()
{
  while (wifi_->status() != WL_CONNECTED) {
    Serial.println("WiFi not connected ...");
    delay(1000);
  }
  Serial.print("WiFi connected at IP: ");
  Serial.println(wifi_->localIP());
  Serial.println("Signing up to Firebase");

  Firebase.reconnectWiFi(true);
  fbdo_.setResponseSize(4096);

  /* Assign the callback function for the long running token generation task */
  config_.token_status_callback =
    tokenStatusCallback;  // see addons/TokenHelper.h

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

void FireLogger::set_int(const char * path, int value)
{
  if (!Firebase.RTDB.setInt(&fbdo_, full_path(path), value)) {
    print_error();
  }
}

void FireLogger::set_float(const char * path, float value)
{
  if (!Firebase.RTDB.setFloat(&fbdo_, full_path(path), value)) {
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

bool FireLogger::is_ready() { return Firebase.ready(); }