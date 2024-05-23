<template>
  <div class="login-container">
    <h2>登录</h2>
    <button @click="goToChangePassword">
      修改密码
    </button>
    <button @click="goToForgotPassword">
      忘记密码？
    </button>
    <form @submit.prevent="handleSubmit">
      <div>
        <label for="username">用户名:</label>
        <input type="text" id="username" v-model="username" required>
      </div>
      <div>
        <label for="password">密码:</label>
        <input type="password" id="password" v-model="password" required>
      </div>
      <button type="submit">登录</button>
      <p v-if="loginError">{{ loginError }}</p> <!-- 显示登录错误信息 -->
      <p v-if="output">{{ output }}</p> <!-- 新增：显示从后端接收的输出 -->
    </form>
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
    const loginError = ref(''); // 用于存储登录错误信息
    const output = ref('');     // 存储后端发来的信息
    const router = useRouter();

    const handleSubmit = async () => {
      try {
        const response = await axios.post('http://localhost:3000/api/login', {
          username: username.value,
          password: password.value
        });
        if (response.status === 200) {
          output.value = response.data; // 将后端返回的输出存储在 output 变量中
          if (output.value === '登录成功') {
            alert('登录成功');
            router.push('/dashboard');
          }
        }
      } catch (error) {
        // 网络或其他错误处理
        loginError.value = '登录过程中发生错误。';
      }
    };

    const goToForgotPassword = () => {
      router.push('/forgot-password');
    };

    const goToChangePassword = () => {
      router.push('/change-password');
    };

    // 返回响应式引用供模板使用
    return {
      username,
      password,
      loginError,
      output,
      handleSubmit,
      goToForgotPassword,
      goToChangePassword
    };
  }


};
</script>


<style scoped>
/* 您的样式 */
.login-container {
  /* 容器样式 */
}
</style>