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

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'package:firebase_core/firebase_core.dart';
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
