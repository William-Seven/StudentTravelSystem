<!-- myForgotPassword.vue -->
<template>
    <div class="forgot-password-container">
        <h2>找回密码</h2>
        <form @submit.prevent="handleForgotPassword">
            <div>
                <label for="username">用户名:</label>
                <input type="text" id="username" v-model="username" required>
            </div>
            <button type="submit">找回密码</button>
            <p v-if="error">{{ error }}</p> <!-- 显示错误信息 -->
            <p v-if="output">{{ output }}</p> <!-- 显示成功消息或其他信息 -->
        </form>
        <button v-if="showLoginButton" @click="goToLogin">返回登录页面</button>
    </div>
</template>

<script>
import axios from 'axios';
import { ref } from 'vue';
import { useRouter } from 'vue-router';

export default {
    name: 'myForgotPassword',
    setup() {
        const username = ref('');
        const error = ref(''); // 用于存储错误信息
        const output = ref(''); // 用于存储成功消息或其他信息
        const showLoginButton = ref(false); // 控制登录按钮显示的变量
        const router = useRouter(); // 创建 router 实例

        const handleForgotPassword = async () => {
            try {
                const response = await axios.post('http://localhost:3000/api/forgot-password', {
                    username: username.value
                });

                if (response.status === 200) {
                    // 处理找回密码成功的逻辑
                    output.value = response.data;
                    if (output.value !== '用户名不存在！') {
                        showLoginButton.value = true; // 显示登录按钮
                    }
                }
            } catch (error) {
                // 网络或其他错误处理
                error.value = '找回密码过程中发生错误：' + error.message;
            }
        };

        const goToLogin = () => {
            router.push('/login'); // 导航到登录页面
        };

        // 返回响应式引用供模板使用
        return {
            username,
            error,
            output,
            showLoginButton,
            handleForgotPassword,
            goToLogin
        };
    }
};
</script>