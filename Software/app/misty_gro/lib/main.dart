// Importing important packages require to connect
// Flutter and Dart
import 'dart:ffi';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:intl/intl.dart';

import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:misty_gro/main_page.dart';
import 'firebase_options.dart';
import 'package:misty_gro/main_page.dart';

// Main Function
void main() async {
  SystemChrome.setEnabledSystemUIMode(SystemUiMode.immersive);
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      // theme of the widget
      theme: ThemeData(
          primarySwatch: Colors.green,
          brightness: Brightness.dark,
          listTileTheme: const ListTileThemeData(
            // textColor: Colors.black,
            tileColor: Colors.black54,
          ),
          cardTheme: const CardTheme(
            color: Colors.black54,
          )),
      // Inner UI of the application
      home: const MainPage(),
      debugShowCheckedModeBanner: false,
    );
  }
}
