import 'package:fl_chart/fl_chart.dart';
import 'package:flutter/material.dart';

import 'data.dart';

class Chart extends StatefulWidget {
  final String title;
  final double minY;
  final double maxY;
  final List<DataPoint> points;
  final MaterialColor color;
  const Chart(
      {super.key,
      required this.title,
      required this.points,
      required this.minY,
      required this.maxY,
      this.color = Colors.green});

  @override
  State<Chart> createState() => _ChartState();
}

class _ChartState extends State<Chart> {
  SideTitles get _bottomTitles => SideTitles(
        showTitles: true,
        getTitlesWidget: (value, meta) {
          String text = '';
          switch (value.toInt()) {
            case 1:
              text = 'Jan';
              break;
            case 3:
              text = 'Mar';
              break;
            case 5:
              text = 'May';
              break;
            case 7:
              text = 'Jul';
              break;
            case 9:
              text = 'Sep';
              break;
            case 11:
              text = 'Nov';
              break;
          }

          return Text(text);
        },
      );

  @override
  Widget build(BuildContext context) {
    return Card(
      shape: const RoundedRectangleBorder(
          borderRadius: BorderRadius.all(Radius.circular(8.0))),
      child: Container(
        margin: const EdgeInsets.fromLTRB(15, 10, 20, 0),
        width: MediaQuery.of(context).size.width,
        height: 220,
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Padding(
              padding: const EdgeInsets.only(top: 8.0, bottom: 8.0),
              child: Text(
                widget.title,
                style:
                    const TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
              ),
            ),
            AspectRatio(
              aspectRatio: 2,
              child: LineChart(
                LineChartData(
                  minX: 0,
                  maxX: 24,
                  minY: widget.minY,
                  maxY: widget.maxY,
                  lineBarsData: [
                    LineChartBarData(
                      spots: widget.points
                          .map((point) => FlSpot(point.x, point.y))
                          .toList(),
                      isCurved: false,
                      dotData: const FlDotData(
                        show: false,
                      ),
                      color: widget.color,

                      // dotData: FlDotData(
                      //   show: false,
                      // ),
                    ),
                  ],
                  borderData: FlBorderData(
                      border: const Border(
                          bottom: BorderSide(color: Colors.white),
                          left: BorderSide(color: Colors.white))),
                  gridData: const FlGridData(show: false),
                  titlesData: const FlTitlesData(
                    // bottomTitles: AxisTitles(sideTitles: _bottomTitles),
                    bottomTitles: AxisTitles(
                        sideTitles: SideTitles(showTitles: true),
                        axisNameWidget: Text('Time (hours)')),
                    leftTitles:
                        AxisTitles(sideTitles: SideTitles(showTitles: false)),
                    topTitles:
                        AxisTitles(sideTitles: SideTitles(showTitles: false)),
                    rightTitles:
                        AxisTitles(sideTitles: SideTitles(showTitles: false)),
                  ),
                  lineTouchData: LineTouchData(
                      enabled: true,
                      // touchCallback:
                      //     (FlTouchEvent event, LineTouchResponse? touchResponse) {
                      //   // TODO : Utilize touch event here to perform any operation
                      // },
                      touchTooltipData: LineTouchTooltipData(
                        tooltipBgColor: widget.color,
                        tooltipRoundedRadius: 20.0,
                        // showOnTopOfTheChartBoxArea: true,
                        fitInsideHorizontally: true,
                        tooltipMargin: 0,
                        getTooltipItems: (touchedSpots) {
                          return touchedSpots.map(
                            (LineBarSpot touchedSpot) {
                              const textStyle = TextStyle(
                                fontSize: 10,
                                fontWeight: FontWeight.w700,
                                color: Colors.white,
                              );
                              return LineTooltipItem(
                                "${widget.points[touchedSpot.spotIndex].x.toStringAsFixed(2)}, ${widget.points[touchedSpot.spotIndex].y.toStringAsFixed(2)}",
                                textStyle,
                              );
                            },
                          ).toList();
                        },
                      ),
                      getTouchedSpotIndicator:
                          (LineChartBarData barData, List<int> indicators) {
                        return indicators.map(
                          (int index) {
                            const line = FlLine(
                                color: Colors.grey,
                                strokeWidth: 1,
                                dashArray: [2, 4]);
                            return const TouchedSpotIndicatorData(
                              line,
                              FlDotData(show: false),
                            );
                          },
                        ).toList();
                      },
                      getTouchLineEnd: (_, __) => double.infinity),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
