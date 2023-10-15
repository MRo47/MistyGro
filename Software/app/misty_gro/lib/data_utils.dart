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

library data_utils;

import 'package:firebase_database/firebase_database.dart';
// import 'data.dart';

class DataPoint {
  final DateTime time;
  final double val;

  DataPoint({required this.time, required this.val});

  @override
  String toString() {
    return "$time, $val\n";
  }
}

List<DataPoint> getPoints<T>(DataSnapshot snapshot) {
  if (!snapshot.exists) {
    return <DataPoint>[];
    //  StampedValue("null", DateTime(0));
  }

  if (T != bool && T != double) {
    throw UnimplementedError("Only bool and double value are supported");
  }

  final children = snapshot.children;

  final points = <DataPoint>[];

  for (final child in children) {
    final timeStamp =
        DateTime.fromMillisecondsSinceEpoch(int.parse(child.key!) * 1000);

    if (T == double) {
      points.add(DataPoint(
          time: timeStamp, val: double.parse(child.value.toString())));
    } else if (T == bool) {
      points.add(DataPoint(
          time: timeStamp,
          val: bool.parse(child.value.toString()) ? 1.0 : 0.0));
    }
  }

  points.sort((dataPt1, dataPt2) => dataPt1.time.compareTo(dataPt2.time));

  return points;
}
