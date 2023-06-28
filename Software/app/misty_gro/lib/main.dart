// Importing important packages require to connect
// Flutter and Dart
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

// Main Function
void main() {
  SystemChrome.setEnabledSystemUIMode(SystemUiMode.immersive);
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

// This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      // title of the application
      title: 'Hello World Demo Application',
      // theme of the widget
      theme: ThemeData(
        primarySwatch: Colors.teal,
        brightness: Brightness.dark,
        // listTileTheme: const ListTileThemeData(
        //   textColor: Colors.black,
        //   tileColor: Colors.white,
        // ),
      ),
      // Inner UI of the application
      home: const MyHomePage(title: 'MistyGro'),
    );
  }
}

/* This class is similar to MyApp instead it
returns Scaffold Widget */
class MyHomePage extends StatelessWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);
  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          actions: const <Widget>[
            Padding(
              padding: EdgeInsets.only(right: 150),
              child: Icon(
                Icons.eco,
                color: Colors.green,
                size: 40,
              ),
            ),
          ],
          // leading:
          title: Text(title),
          titleTextStyle: const TextStyle(
            fontSize: 40,
            fontWeight: FontWeight.bold,
            // color: Colors.teal,
          ),
          toolbarHeight: 70,
          backgroundColor: Colors.black,
        ),
        // Sets the content to the
        // center of the application page
        body: ListView(
          children: const <Widget>[
            Card(
              child: ListTile(
                title: Text('Misters'),
                subtitle: Text('Last on: 5 minutes ago'),
                trailing: Icon(
                  Icons.water_drop,
                  color: Colors.blue,
                ),
              ),
            ),
            Card(
              child: ListTile(
                title: Text('Light'),
                subtitle: Text('Last on: 10 minutes ago'),
                trailing: Icon(
                  Icons.light_mode,
                  color: Colors.amber,
                ),
              ),
            ),
            Card(
              child: ListTile(
                title: Text('Temperature'),
                subtitle: Text('15 deg celsius'),
                trailing: Icon(
                  Icons.thermostat,
                  color: Colors.red,
                ),
              ),
            ),
            Card(
              child: ListTile(
                title: Text('pH'),
                subtitle: Text('4.5'),
                trailing: Icon(
                  Icons.science,
                  color: Colors.green,
                ),
              ),
            ),
            Card(
              child: ListTile(
                title: Text('TDS'),
                subtitle: Text('1000ppm'),
                trailing: Icon(
                  Icons.contrast,
                  color: Colors.brown,
                ),
              ),
            )
          ],
        ));
  }
}
