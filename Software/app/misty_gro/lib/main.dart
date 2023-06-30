// Importing important packages require to connect
// Flutter and Dart
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:intl/intl.dart';

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
        bottomNavigationBar: BottomNavigationBar(
          items: const <BottomNavigationBarItem>[
            BottomNavigationBarItem(
              icon: Icon(Icons.home),
              label: 'Home',
            ),
            BottomNavigationBarItem(
              icon: Icon(Icons.settings),
              label: 'Settings',
            ),
          ],
          backgroundColor: Colors.black,
          selectedItemColor: Colors.green,
        ),
        // Sets the content to the
        // center of the application page
        body: ListView(
          children: <Widget>[
            RelayCard(
              name: 'Mister',
              lastUpdate: DateTime.now(),
              icon: Icons.water_drop,
              switchOn: true,
              onColor: Colors.blue,
            ),
            RelayCard(
              name: 'Light',
              lastUpdate: DateTime.now(),
              icon: Icons.light_mode,
              switchOn: true,
              onColor: Colors.amber,
            ),
            SensorCard(
              name: 'Temperature',
              lastUpdate: DateTime.now(),
              icon: Icons.thermostat,
              iconColor: Colors.red,
              value: 18.54,
              units: '°C',
            ),
            SensorCard(
              name: 'LDR',
              lastUpdate: DateTime.now(),
              icon: Icons.blur_circular, // Icons.table_chart_rounded,
              iconColor: Colors.deepOrange.shade900,
              value: 4.86,
              units: 'V',
            ),
            Card(
              child: ListTile(
                title: Text(
                  'pH',
                  style: TextStyle(fontSize: 20),
                ),
                subtitle: Text('4.5'),
                trailing: Icon(
                  Icons.science,
                  color: Colors.green,
                  size: 40,
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
            ),
          ],
        ));
  }
}

class RelayCard extends StatelessWidget {
  final String name;
  final DateTime lastUpdate;
  final IconData icon;
  final bool switchOn;
  final Color onColor;

  const RelayCard(
      {super.key,
      required this.name,
      required this.lastUpdate,
      required this.icon,
      required this.switchOn,
      required this.onColor});

  @override
  Widget build(BuildContext context) {
    return Card(
      child: SizedBox(
        width: double.infinity,
        child: Padding(
          padding: const EdgeInsets.all(15.0),
          child: SizedBox(
            width: MediaQuery.of(context).size.width,
            child: Row(
              children: <Widget>[
                Expanded(
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: <Widget>[
                      Padding(
                        padding: const EdgeInsets.only(bottom: 20),
                        child: Text(
                          name,
                          style: const TextStyle(
                              fontSize: 20, fontWeight: FontWeight.bold),
                        ),
                      ),
                      Text(
                        "Last update: ${DateFormat('yyyy-MM-dd kk:mm').format(lastUpdate)}",
                        style:
                            const TextStyle(fontSize: 15, color: Colors.grey),
                      )
                    ],
                  ),
                ),
                Container(
                  alignment: Alignment.centerRight,
                  width: MediaQuery.of(context).size.width * 0.3,
                  child: Padding(
                    padding: const EdgeInsets.all(15.0),
                    child: Icon(
                      icon,
                      color: switchOn == true ? onColor : Colors.grey.shade800,
                      size: 40,
                    ),
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}

class SensorCard extends StatelessWidget {
  final String name;
  final DateTime lastUpdate;
  final IconData icon;
  final Color iconColor;
  final double value;
  final String units;

  const SensorCard(
      {super.key,
      required this.name,
      required this.lastUpdate,
      required this.icon,
      required this.iconColor,
      required this.value,
      required this.units});

  @override
  Widget build(BuildContext context) {
    return Card(
      child: SizedBox(
        width: double.infinity,
        child: Padding(
          padding: const EdgeInsets.all(15.0),
          child: SizedBox(
            width: MediaQuery.of(context).size.width,
            child: Row(
              children: <Widget>[
                Expanded(
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: <Widget>[
                      Padding(
                        padding: const EdgeInsets.only(bottom: 20),
                        child: Text(
                          '$name: $value $units',
                          style: const TextStyle(
                              fontSize: 20, fontWeight: FontWeight.bold),
                        ),
                      ),
                      Text(
                        "Last update: ${DateFormat('yyyy-MM-dd kk:mm').format(lastUpdate)}",
                        style:
                            const TextStyle(fontSize: 15, color: Colors.grey),
                      )
                    ],
                  ),
                ),
                Container(
                  alignment: Alignment.centerRight,
                  width: MediaQuery.of(context).size.width * 0.3,
                  child: Padding(
                    padding: const EdgeInsets.all(15.0),
                    child: Icon(
                      icon,
                      color: iconColor,
                      size: 40,
                    ),
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
