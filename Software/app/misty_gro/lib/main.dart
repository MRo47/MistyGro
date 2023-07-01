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
      home: MyHomePage(title: 'MistyGro'),
    );
  }
}

/* This class is similar to MyApp instead it
returns Scaffold Widget */
class MyHomePage extends StatelessWidget {
  MyHomePage({Key? key, required this.title}) : super(key: key);
  final String title;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          actions: const <Widget>[
            Icon(Icons.menu),
          ],
          // leading:
          title: Row(
            children: [
              Text(title),
              const Image(
                image: AssetImage('assets/mistygro_512.png'),
                width: 45,
              )
            ],
          ),
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
          children: <Widget>[
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Text(
                'Relays',
                style: TextStyle(color: Colors.grey.shade500),
              ),
            ),
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
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Text(
                'Sensors',
                style: TextStyle(color: Colors.grey.shade500),
              ),
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
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Text(
                'Manual inputs',
                style: TextStyle(color: Colors.grey.shade500),
              ),
            ),
            ManualInputCard(
              name: 'pH',
              lastUpdate: DateTime.now(),
              icon: Icons.science, // Icons.table_chart_rounded,
              iconColor: Colors.green,
              initValue: 6.8,
              units: '',
            ),
            ManualInputCard(
              name: 'TDS',
              lastUpdate: DateTime.now(),
              icon: Icons.opacity, // Icons.table_chart_rounded,
              iconColor: Colors.blueGrey,
              initValue: 6.8,
              units: 'ppm',
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

class ManualInputCard extends StatefulWidget {
  final String name;
  final DateTime lastUpdate;
  final IconData icon;
  final Color iconColor;
  final double initValue;
  final String units;

  const ManualInputCard({
    super.key,
    required this.name,
    required this.lastUpdate,
    required this.icon,
    required this.iconColor,
    required this.initValue,
    required this.units,
  });

  @override
  State<ManualInputCard> createState() => _ManualInputCardState();
}

class _ManualInputCardState extends State<ManualInputCard> {
  final _textFieldController = TextEditingController();
  late double value;

  @override
  void initState() {
    super.initState();
    value = widget.initValue;
  }

  @override
  Widget build(BuildContext context) {
    return InkWell(
      onTap: () async {
        var gotValue = await _showTextInputDialog(context);
        if (gotValue != null) {
          setState(() {
            value = double.parse(gotValue);
          });
        }
      },
      child: SensorCard(
        name: widget.name,
        lastUpdate: widget.lastUpdate,
        icon: widget.icon, // Icons.table_chart_rounded,
        iconColor: widget.iconColor,
        value: value,
        units: widget.units,
      ),
    );
  }

  Future<String?> _showTextInputDialog(BuildContext context) async {
    return showDialog(
        context: context,
        builder: (context) {
          return AlertDialog(
            title: const Text('Sensor reading'),
            content: TextField(
              controller: _textFieldController,
              keyboardType:
                  const TextInputType.numberWithOptions(decimal: true),
              decoration: const InputDecoration(hintText: "Enter value"),
            ),
            actions: <Widget>[
              TextButton(
                child: const Text("Cancel"),
                onPressed: () => Navigator.pop(context),
              ),
              TextButton(
                child: const Text('Submit'),
                onPressed: () =>
                    Navigator.pop(context, _textFieldController.text),
              ),
            ],
          );
        });
  }
}
