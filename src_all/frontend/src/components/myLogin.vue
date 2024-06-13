<template>
  <div class="login-container">
    <div class="stars" ref="starsRef">
      <div class="star" v-for="(item, index) in starsCount" :key="index"></div>
    </div>
    <form class="form" @submit.prevent="handleSubmit">
      <h2 class="title_login">登录</h2>
      <button class="change_password" @click="goToChangePassword">
        修改密码
      </button>
      <button class="forget_password" @click="goToForgotPassword">
        忘记密码
      </button>
      <div class="form1" >
        <label for="username">用户名:</label>
        <input type="text" id="username" v-model="username" required>
      </div>
      <div class="form2" >
        <label for="password">密码:</label>
        <input type="password" id="password" v-model="password" required>
      </div>
      <button class="login_button" type="submit">登录</button>
      <p class="error1" v-if="loginError">{{ loginError }}</p> <!-- 显示登录错误信息 -->
      <p class="error2" v-if="output">{{ output }}</p> <!-- 新增：显示从后端接收的输出 -->
    </form>
  </div>
</template>

<script>
import axios from 'axios';
import { ref } from 'vue';
import { useRouter } from 'vue-router';
import { onMounted } from "vue";

export default {
  setup() {
    // 登录相关的响应式引用和方法
    const username = ref('');
    const password = ref('');
    const loginError = ref(''); // 用于存储登录错误信息
    const output = ref('');    // 存储后端发来的信息
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

    // 星空效果相关的响应式引用和方法
    let starsRef = ref(null);
    const starsCount = 800; // 星星数量
    const distance = 900; // 间距

    onMounted(() => {
      let starNodes = Array.from(starsRef.value.children);
      starNodes.forEach((item) => {
        let speed = 0.2 + Math.random() * 1;
        let thisDistance = distance + Math.random() * 300;
        item.style.transformOrigin = `0 0 ${thisDistance}px`;
        item.style.transform = `
        translate3d(0,0,-${thisDistance}px)
        rotateY(${Math.random() * 360}deg)
        rotateX(${Math.random() * -50}deg)
        scale(${speed},${speed})`;
      });
    });

    // 返回所有响应式引用和方法供模板使用
    return {
      username,
      password,
      loginError,
      output,
      handleSubmit,
      goToForgotPassword,
      goToChangePassword,
      starsRef,
      starsCount,
    };
  }
};
</script>


<style scoped>
.title_login {
  color: #fefefe;
  font-size: 4em; /* 设置字号大小 */
  margin:0%;
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  margin-top: 0vh; /* 从视口顶部向下移动20% */
  text-align: center;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
}

.form {
  position: absolute;
  bottom: 50%;
  left: 50%;
  transform: translate(-50%, -10%);
  width: 500px;
  height: 350px;
  background: rgba(255, 255, 255, 0.2);
  backdrop-filter: blur(10px);
  border-radius: 20px; /* 设置圆角为20像素 */
  /* 其他样式，例如边框、阴影等 */
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); /* 添加轻微的阴影效果 */
}

.form1, .form2 {
  align-items: center; /* 垂直居中 */
  color: #fefefe;
  font-size: 2.5em;
  font-family: 'STKaiti', 'KaiTi', sans-serif;
  position: relative;
  left: -10%;
  margin: 0;
  text-align: right; /* 这会让内部的input元素右对齐 */
}

label {
  margin-right: 10px; /* 标签和输入框之间增加间距 */
}

input {
  height: 2em;
  width: 55%;
}

button {
  justify-content: space-between;
  margin: auto;
  position: absolute;
  font-size: 2em;
  border: 1px solid #000; /* 边框样式，可以根据需要调整 */
  cursor: pointer; /* 鼠标悬停时显示指针手势 */
  border-radius: 8px; /* 添加圆角 */
}

.change_password {
  position: absolute;
  bottom: 10%;
  left: 19%;
  transform: translateX(-50%);
  font-size: 1.5em;
  cursor: pointer;
}

.forget_password {
  position: absolute;
  bottom: 10%;
  right: -4%;
  transform: translateX(-50%);
  font-size: 1.5em;
  cursor: pointer;
}

.error1, .error2 {
  position: absolute;
  bottom: 30%;
  left: 50%;
  transform: translateX(-50%);
  color: #fefefe;
  font-size: 1em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  text-align: center;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
}

.login_button {
  position: absolute;
  bottom: 25%;
  left: 50%;
  transform: translateX(-50%);
  font-size: 1.5em;
  cursor: pointer;
  width: 85%;
}

button:hover {
  background-color: #56cfcf;
}

.login-container {
  position: absolute;
  width: 100%;
  height: 100%;
  margin: 0;
  padding: 0;
  background-attachment: fixed;
  overflow: hidden;
  background-image: url('~@/assets/img/background.png');
  background-size: cover;
}

@keyframes rotate {
  0% {
    transform: perspective(400px) rotateZ(20deg) rotateX(-40deg) rotateY(0);
  }
  100% {
    transform: perspective(400px) rotateZ(20deg) rotateX(-40deg)
      rotateY(-360deg);
  }
}
.stars {
  transform: perspective(500px);
  transform-style: preserve-3d;
  position: absolute;
  perspective-origin: 50% 100%;
  left: 45%;
  animation: rotate 90s infinite linear;
  bottom: 0;
}
.star {
  width: 2px;
  height: 2px;
  background: #f7f7b6;
  position: absolute;
  left: 0;
  top: 0;
  backface-visibility: hidden;
}
</style>