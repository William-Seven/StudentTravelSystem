<!-- myChangePassword.vue -->
<template>
    <div class="change-password-container">
        <h2>修改密码</h2>
        <form @submit.prevent="handleChangePassword">
            <div>
                <label for="username">用户名:</label>
                <input type="text" id="username" v-model="username" required>
            </div>
            <div>
                <label for="oldPassword">旧密码:</label>
                <input type="password" id="oldPassword" v-model="oldPassword" required>
            </div>
            <div>
                <label for="newPassword">新密码:</label>
                <input type="password" id="newPassword" v-model="newPassword" required>
            </div>
            <button type="submit">修改密码</button>
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
    name: 'myChangePassword',
    setup() {
        const username = ref('');
        const oldPassword = ref('');
        const newPassword = ref('');
        const error = ref(''); // 用于存储错误信息
        const output = ref(''); // 用于存储成功消息或其他信息
        const showLoginButton = ref(false); // 控制登录按钮显示的变量
        const router = useRouter();

        const handleChangePassword = async () => {
            try {
                const response = await axios.post('http://localhost:3000/api/change-password', {
                    username: username.value,
                    oldPassword: oldPassword.value,
                    newPassword: newPassword.value
                });

                if (response.status === 200) {
                    // 处理修改密码成功的逻辑
                    output.value = response.data;
                    if (output.value === '密码修改成功！') {
                        //alert(output.value);
                        //router.push('/login');
                        showLoginButton.value = true; // 显示登录按钮
                    }
                    // 可以在这里添加重定向到登录页面或其他页面的逻辑
                }
            } catch (error) {
                // 网络或其他错误处理
                error.value = '修改密码过程中发生错误：' + error.message;
            }
        };

        const goToLogin = () => {
            router.push('/login');
        };

        // 返回响应式引用供模板使用
        return {
            username,
            oldPassword,
            newPassword,
            error,
            output,
            handleChangePassword,
            goToLogin,
            showLoginButton
        };
    }
};
</script>