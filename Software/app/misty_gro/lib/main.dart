import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  SystemChrome.setPreferredOrientations([
    DeviceOrientation.portraitUp,
    DeviceOrientation.portraitDown,
  ]).then((value) => runApp(MyApp()));
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    // 1 <-- SEE HERE
    return const CupertinoApp(
      // 2 <-- SEE HERE
      theme: CupertinoThemeData(brightness: Brightness.dark),
      home: CupertinoSimpleHomePage(),
    );
  }
}

class CupertinoSimpleHomePage extends StatefulWidget {
  const CupertinoSimpleHomePage({Key? key}) : super(key: key);

  @override
  _CupertinoSimpleHomePageState createState() =>
      _CupertinoSimpleHomePageState();
}

class _CupertinoSimpleHomePageState extends State<CupertinoSimpleHomePage> {
  List<int> bottom = <int>[0];

  @override
  Widget build(BuildContext context) {
    const Key centerKey = ValueKey<String>('bottom-sliver-list');
    // 3 <-- SEE HERE
    return CupertinoTabScaffold(
      // 2 <-- SEE HERE
      tabBar: CupertinoTabBar(
        currentIndex: 1,
        items: const <BottomNavigationBarItem>[
          // 3 <-- SEE HERE
          BottomNavigationBarItem(
              icon: Icon(CupertinoIcons.home), label: 'Home'),
          BottomNavigationBarItem(
              icon: Icon(CupertinoIcons.settings), label: 'Settings'),
        ],
      ),
      tabBuilder: (context, index) {
        late final CupertinoTabView returnValue;
        switch (index) {
          case 0:
            // 4 <-- SEE HERE
            returnValue = CupertinoTabView(
              builder: (context) {
                return CustomScrollView(
                  slivers: <Widget>[
                    CupertinoSliverNavigationBar(
                      largeTitle: Text('MistyGro'),
                    ),
                    SliverList(
                      key: centerKey,
                      delegate: SliverChildBuilderDelegate(
                        (BuildContext context, int index) {
                          return const Card(
                            child: ListTile(
                              // leading:
                              //     Icon(Icons.water_drop, color: Colors.blue),
                              title: Text('Misters'),
                              trailing:
                                  Icon(Icons.water_drop, color: Colors.blue),
                            ),
                          );
                        },
                        childCount: bottom.length,
                      ),
                    ),
                  ],
                );
              },
            );
            break;
          case 1:
            returnValue = CupertinoTabView(
              builder: (context) {
                return const Text('World');
              },
            );
            break;
        }
        return returnValue;
      },
    );
  }
}
