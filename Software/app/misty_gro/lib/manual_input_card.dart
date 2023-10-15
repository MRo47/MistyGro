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

import 'package:misty_gro/sensor_card.dart';

class ManualInputCard extends StatefulWidget {
  final String name;
  final DateTime lastUpdate;
  final IconData icon;
  final Color iconColor;
  final double initValue;
  final String units;
  final Function(double value) onGotValue;

  const ManualInputCard({
    super.key,
    required this.name,
    required this.lastUpdate,
    required this.icon,
    required this.iconColor,
    required this.initValue,
    required this.units,
    required this.onGotValue,
  });

  @override
  State<ManualInputCard> createState() => _ManualInputCardState();
}

class _ManualInputCardState extends State<ManualInputCard> {
  final _textFieldController = TextEditingController();
  double _value = 0.0;

  @override
  void initState() {
    super.initState();
    _value = widget.initValue;
  }

  @override
  Widget build(BuildContext context) {
    return InkWell(
      onTap: () async {
        var gotValue = await _showTextInputDialog(context);
        if (gotValue != null) {
          setState(() {
            _value = double.parse(gotValue);
            widget.onGotValue(_value);
          });
        }
      },
      child: SensorCard(
        name: widget.name,
        lastUpdate: widget.lastUpdate,
        icon: widget.icon, // Icons.table_chart_rounded,
        iconColor: widget.iconColor,
        value: _value,
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
            shape: const RoundedRectangleBorder(
                borderRadius: BorderRadius.all(Radius.circular(10))),
            backgroundColor: Colors.grey.shade900,
            content: TextField(
              controller: _textFieldController,
              keyboardType:
                  const TextInputType.numberWithOptions(decimal: true),
              decoration: const InputDecoration(hintText: "Enter value"),
            ),
            actionsAlignment: MainAxisAlignment.spaceBetween,
            actions: <Widget>[
              IconButton(
                icon: const Icon(
                  Icons.close,
                  color: Colors.green,
                ),
                onPressed: () => Navigator.pop(context),
              ),
              IconButton(
                icon: const Icon(
                  Icons.done,
                  color: Colors.green,
                ),
                onPressed: () =>
                    Navigator.pop(context, _textFieldController.text),
              ),
            ],
          );
        });
  }
}
