<template>
    <div class="register-container">
        <h2>注册</h2>
        <form @submit.prevent="handleSubmit">
            <div>
                <label for="username">用户名:</label>
                <input type="text" id="username" v-model="username" required>
            </div>
            <div>
                <label for="password">密码:</label>
                <input type="password" id="password" v-model="password" required>
            </div>
            <div>
                <label for="confirmPassword">确认密码:</label>
                <input type="password" id="confirmPassword" v-model="confirmPassword" required>
            </div>
            <button type="submit">注册</button>
            <p v-if="registerError">{{ registerError }}</p> <!-- 显示注册错误信息 -->
            <p v-if="output">{{ output }}</p> <!-- 新增：显示从后端接收的输出 -->
        </form>
        <button v-if="showLoginButton" @click="goToLogin">返回登录页面</button>
    </div>
</template>

<script>
import axios from 'axios';
import { ref } from 'vue';
import { useRouter } from 'vue-router';

export default {
    setup() {
        const username = ref('');
        const password = ref('');
        const confirmPassword = ref('');
        const registerError = ref(''); // 用于存储注册错误信息
        const output = ref('');
        const showLoginButton = ref(false); // 控制登录按钮显示的变量
        const router = useRouter();

        const handleSubmit = async () => {
            if (password.value !== confirmPassword.value) {
                registerError.value = '两次输入的密码不一致。';
                return;
            }

            try {
                const response = await axios.post('http://localhost:3000/api/register', {
                    username: username.value,
                    password: password.value
                });
                if (response.status === 200) {
                    output.value = response.data; // 将后端返回的输出存储在 output 变量中
                    // 注册成功处理
                    if (response.data === '注册成功') {
                        //alert('注册成功');
                        //router.push('/login'); // 注册成功后跳转到登录页面
                        showLoginButton.value = true; // 显示登录按钮
                    }
                    // 这里可以添加代码来处理注册成功的逻辑，如跳转到登录页面
                }
            } catch (error) {
                // 网络或其他错误处理
                registerError.value = '注册过程中发生错误。' + error.message;
            }
        };

        const goToLogin = () => {
            router.push('/login'); // 跳转到登录页面
        };

        // 返回响应式引用供模板使用
        return {
            username,
            password,
            confirmPassword,
            registerError,
            output,
            handleSubmit,
            goToLogin,
            showLoginButton
        };
    }
};
</script>