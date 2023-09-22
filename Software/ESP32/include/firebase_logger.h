#ifndef _FIREBASE_LOGGER_H_
#define _FIREBASE_LOGGER_H_

#include <FirebaseESP32.h>
#include <WiFi.h>

/**
 * @brief Firebase RTDB logger
 * 
 */
class FireLogger
{
private:
  FirebaseAuth auth_;
  FirebaseConfig config_;
  FirebaseData fbdo_;
  String path_prefix_;

  // print errors from last operation
  void print_error();

  // add path prefix for specific user
  MB_String full_path(const char * path);

public:
  FireLogger();

  /**
   * @brief initialise and authorise system to use Firebase RTDB (real time database)
   * make sure wifi is initialised before calling this method
   * 
   * @param fire_url Firebase url for the RTDB
   * @param fire_token Token for auth
   * @param email user email
   * @param pass user password
   */
  void begin(
    const char * fire_url, const char * fire_token, const char * email,
    const char * pass);

  /**
   * @brief Set an integer value
   * 
   * @param path relative path for the user
   * @param value int value
   */
  void set_int(const char * path, int64_t value);

  /**
   * @brief Set a float value
   * 
   * @param path relative path for the user
   * @param value float value
   */
  void set_float(const char * path, double value);

  /**
   * @brief Set a string value
   * 
   * @param path relative path for the user
   * @param value char* value
   */
  void set_string(const char * path, const char * value);

  /**
   * @brief Set a bool value
   * 
   * @param path relative path for the user
   * @param value bool value
   */
  void set_bool(const char * path, bool value);

  /**
   * @brief Push a timestamp into a list to a relative path, useful to log times like
   * when initialisation was completed
   * 
   * @param path relative path for the user
   * @param timestamp time_t type timestamp
   */
  void push_time(const char * path, time_t timestamp);

  /**
   * @brief Check if authenticated
   * 
   * @return true if authenticated
   */
  bool is_ready();

  /**
   * @brief Get TCP keepalive status
   * 
   * @return true if TCP keepalive is set
   */
  bool is_keep_alive();

  /**
   * @brief Get http server connection status
   * 
   * @return true if connected
   */
  bool is_connected();

  /**
 * @brief refresh token if expired
 * 
 * @return true if token refreshed
 */
  bool check_and_refresh_token();
};

#endif  // _FIREBASE_LOGGER_H_