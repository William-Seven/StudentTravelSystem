// server.js
const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const app = express();
const port = 3000;

app.use(express.json());
// 使用 cors 中间件，允许所有域名访问
app.use(cors());

//登录api
app.post('/api/login', (req, res) => {
    const { username, password } = req.body;
    const cppProcess = spawn('./login', [username, password, '-1']); // 假设登录程序名为 login

    let output = '';
    cppProcess.stdout.on('data', (data) => {
        output += data.toString();
    });
    cppProcess.on('close', (code) => {
        if (code === 0) {
            // 假设 C++ 程序返回 0 表示登录成功
            res.status(200).send(output);
        }
    });
    cppProcess.on('error', (err) => {
        console.error('Spawn error:', err);
        res.status(500).send('Server error');
    });
});

//注册api
app.post('/api/register', (req, res) => {
    const { username, password } = req.body;
    const cppProcess = spawn('./register', [username, password, '-1']); // 假设注册程序名为 register

    let output = '';
    cppProcess.stdout.on('data', (data) => {
        output += data.toString();
    });

    cppProcess.on('close', (code) => {
        if (code === 0) {
            // 假设 C++ 程序返回 0 表示注册成功
            res.status(200).send(output);
        }
    });

    cppProcess.on('error', (err) => {
        console.error('Spawn error:', err);
        res.status(500).send('Server error');
    });
});

// 找回密码api
app.post('/api/forgot-password', (req, res) => {
    const { username } = req.body;

    const cppProcess = spawn('./forgotpassword', [username, '-1', '-1']);

    let output = '';
    cppProcess.stdout.on('data', (data) => {
        output += data.toString();
    });

    cppProcess.on('close', (code) => {
        if (code === 0) {
            // 假设 C++ 程序返回 0 表示找回密码成功
            res.status(200).send(output);
        }
    });

    cppProcess.on('error', (err) => {
        console.error('Spawn error:', err);
        res.status(500).send(output);
    });
});

//修改密码api
app.post('/api/change-password', (req, res) => {
    const { username, oldPassword, newPassword } = req.body;

    const cppProcess = spawn('./changepassword', [username, oldPassword, newPassword]);

    let output = '';
    cppProcess.stdout.on('data', (data) => {
        output += data.toString();
    });

    cppProcess.on('close', (code) => {
        if (code === 0) {
            // 假设 C++ 程序返回 0 表示修改密码成功
            res.status(200).send(output);
        }
    });

    cppProcess.on('error', (err) => {
        console.error('Spawn error:', err);
        res.status(500).send(output);
    });
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});

