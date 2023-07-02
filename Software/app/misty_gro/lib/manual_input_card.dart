import 'package:flutter/material.dart';
import 'sensor_card.dart';

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
