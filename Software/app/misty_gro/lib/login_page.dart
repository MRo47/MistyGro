import 'package:flutter/material.dart';
import 'package:firebase_auth/firebase_auth.dart';

class LoginPage extends StatefulWidget {
  const LoginPage({super.key});

  @override
  State<LoginPage> createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage> {
  final _emailController = TextEditingController();
  final _passController = TextEditingController();

  Future signIn() async {
    await FirebaseAuth.instance.signInWithEmailAndPassword(
      email: _emailController.text.trim(),
      password: _passController.text.trim(),
    );
  }

  @override
  void dispose() {
    _emailController.dispose();
    _passController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      // Sets the content to the
      // center of the application page
      body: Container(
        margin: const EdgeInsets.only(left: 20, right: 20),
        width: double.infinity,
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            const Image(
              image: AssetImage('assets/mistygro_512.png'),
              width: 150,
            ),
            const Text(
              'MistyGro',
              style: TextStyle(fontSize: 50, fontWeight: FontWeight.w500),
            ),
            const SizedBox(
              height: 30,
            ),
            TextField(
              controller: _emailController,
              decoration: InputDecoration(
                  filled: true,
                  hintText: "Email",
                  border: OutlineInputBorder(
                    borderRadius: BorderRadius.circular(10),
                  )),
            ),
            const SizedBox(
              height: 30,
            ),
            TextField(
              controller: _passController,
              obscureText: true,
              decoration: InputDecoration(
                  filled: true,
                  hintText: "Password",
                  border: OutlineInputBorder(
                    borderRadius: BorderRadius.circular(10),
                  )),
            ),
            const SizedBox(
              height: 40,
            ),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                const Text(
                  'Sign in',
                  style: TextStyle(fontSize: 27, fontWeight: FontWeight.w700),
                ),
                CircleAvatar(
                  radius: 30,
                  backgroundColor: Colors.green.shade600,
                  child: IconButton(
                      color: Colors.white,
                      onPressed: () {
                        signIn();
                      },
                      icon: const Icon(
                        Icons.arrow_forward,
                      )),
                )
              ],
            )
          ],
        ),
      ),
    );
  }
}
