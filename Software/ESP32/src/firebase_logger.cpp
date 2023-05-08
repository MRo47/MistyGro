#include "firebase_logger.h"

//Provide the token generation process info.
#include "addons/TokenHelper.h"

void FireLogger::print_error()
{
  Serial.printf("Error:\ncode: %d\nmsg: ", fbdo_.errorCode());
  Serial.println(fbdo_.errorReason());
}

FireLogger::FireLogger(
  WiFiClass * wifi, const char * fire_url, const char * fire_token)
: wifi_(wifi), signup_ok_(false)
{
  config_.database_url = fire_url;
  config_.api_key = fire_token;
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

  if (Firebase.signUp(&config_, &auth_, "", "")) {
    Serial.println("ok");
    signup_ok_ = true;
  } else {
    Serial.printf("%s\n", config_.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config_.token_status_callback =
    tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config_, &auth_);
  Firebase.reconnectWiFi(true);
}

void FireLogger::set_int(const char * path, int value)
{
  if (!Firebase.RTDB.setInt(&fbdo_, path, value)) {
    print_error();
  }
}

void FireLogger::set_float(const char * path, float value)
{
  if (!Firebase.RTDB.setFloat(&fbdo_, path, value)) {
    print_error();
  }
}

void FireLogger::set_string(const char * path, const char * value)
{
  if (!Firebase.RTDB.setString(&fbdo_, path, value)) {
    print_error();
  }
}

void FireLogger::set_bool(const char * path, bool value)
{
  if (!Firebase.RTDB.setBool(&fbdo_, path, value)) {
    print_error();
  }
}

bool FireLogger::is_ready() { return Firebase.ready() && signup_ok_; }