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

// 游学推荐api
app.post('/api/recommendation', (req, res) => {
    let { filterType, limit, sort, searchKeyword } = req.body;

    let filterArg = filterType === 'all' ? 2 : filterType === 'scenic' ? 0 : 1;
    let limitArg = limit === 'all' ? 1 : 0;
    let sortArg = sort === 'default' ? 2 : sort === 'popularity' ? 0 : 1;
    let searchArg = searchKeyword || '-1'; // 假设C++程序使用-1表示默认关键字

    const args = [filterArg, limitArg, sortArg, searchArg];

    const recommendationProcess = spawn('./recommendation', args);

    let output = '';
    recommendationProcess.stdout.on('data', (data) => {
        output += data.toString();
    });

    recommendationProcess.on('close', (code) => {
        if (code === 0) {
            // 假设C++程序返回0表示成功
            res.status(200).json({
                success: true,
                list: output
            });
        } else {
            // 如果C++程序返回非0值，表示有错误发生
            res.status(500).json({
                success: false,
                error: 'Failed to get recommendations'
            });
        }
    });

    recommendationProcess.on('error', (err) => {
        console.error('Spawn error:', err);
        res.status(500).json({
            success: false,
            error: 'Server internal error'
        });
    });
});

//路线规划api
app.post('/api/route-plan', (req, res) => {
    let { startPoint, endPoint, currentLocation, viaPoints, transport, area } = req.body;

    // 根据area和transport构建调用参数
    let args = [area, transport];
    if (startPoint && endPoint) {
        args.push('1', startPoint, endPoint);
    } else if (currentLocation && viaPoints) {
        args.push('2', currentLocation, ...viaPoints);
    }

    const routePlannerProcess = spawn('./routePlanner', args);

    let output = '';
    routePlannerProcess.stdout.on('data', (data) => {
        output += data.toString().replace(/\n/g, '<br>');
    });

    routePlannerProcess.on('close', (code) => {
        if (code === 0) {
            // 假设 C++ 程序返回 0 表示路线规划成功
            res.status(200).json({
                success: true,
                info: output
            });
        } else {
            // 如果C++程序返回非0值，表示有错误发生
            res.status(200).json({
                success: false,
                error: '路线规划失败'
            });
        }
    });

    routePlannerProcess.on('error', (err) => {
        console.error('Spawn error:', err);
        res.status(500).json({
            success: false,
            error: '服务器内部错误'
        });
    });
});

// 场所查询api
app.post('/api/place-query', (req, res) => {
    let { currentLocation, searchRange, placeType } = req.body;

    const placeQueryProcess = spawn('./placeQuery', [currentLocation, searchRange, placeType]);

    let output = '';
    placeQueryProcess.stdout.on('data', (data) => {
        output += data.toString();
    });

    placeQueryProcess.on('close', (code) => {
        if (code === 0) {
            // 假设C++程序返回0表示成功
            res.status(200).json({
                success: true,
                list: output
            });
        } else {
            // 如果C++程序返回非0值，表示有错误发生
            res.status(500).json({
                success: false,
                error: 'Failed to get places'
            });
        }
    });

    placeQueryProcess.on('error', (err) => {
        console.error('Spawn error:', err);
        res.status(500).json({
            success: false,
            error: 'Server internal error'
        });
    });
});

// 游学日记搜索api
app.post('/api/diary-search', (req, res) => {
    let { title, author, description, content, sort } = req.body;

    const diarySearchProcess = spawn('./diarySearch', [title, author, description, content, sort]);

    let output = '';
    diarySearchProcess.stdout.on('data', (data) => {
        output += data.toString();
    });

    diarySearchProcess.on('close', (code) => {
        if (code === 0) {
            // 假设C++程序返回0表示成功
            res.status(200).json({
                success: true,
                list: output
            });
        } else {
            // 如果C++程序返回非0值，表示有错误发生
            res.status(500).json({
                success: false,
                error: 'Failed to search diaries'
            });
        }
    });

    diarySearchProcess.on('error', (err) => {
        console.error('Spawn error:', err);
        res.status(500).json({
            success: false,
            error: 'Server internal error'
        });
    });
});

// 游学日记下载api


// 游学日记写入api


app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});

