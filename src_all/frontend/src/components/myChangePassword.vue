<!-- myChangePassword.vue -->
<template>
    <div class="change-password-container">
        <div class="stars" ref="starsRef">
            <div class="star" v-for="(item, index) in starsCount" :key="index"></div>
        </div>
        <form class="form" @submit.prevent="handleChangePassword">
            <h2 class="title">修改密码</h2>
            <div class="input1">
                <label for="username">用户名:</label>
                <input type="text" id="username" v-model="username" required>
            </div>
            <div class="input2">
                <label for="oldPassword">旧密码:</label>
                <input type="password" id="oldPassword" v-model="oldPassword" required>
            </div>
            <div class="input3">
                <label for="newPassword">新密码:</label>
                <input type="password" id="newPassword" v-model="newPassword" required>
            </div>
            <button class="submit_button" type="submit">修改密码</button>
            <p class="return_message1" v-if="error">{{ error }}</p> <!-- 显示错误信息 -->
            <p class="return_message2" v-if="output">{{ output }}</p> <!-- 显示成功消息或其他信息 -->
            <button class="return" v-if="showLoginButton" @click="goToLogin">返回登录页面</button>
        </form>
    </div>
</template>

<script>
import axios from 'axios';
import { ref } from 'vue';
import { useRouter } from 'vue-router';
import { onMounted } from "vue";

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

        let starsRef = ref(null);

        const starsCount = 800; //星星数量
        const distance = 900; //间距

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

        // 返回响应式引用供模板使用
        return {
            username,
            oldPassword,
            newPassword,
            error,
            output,
            handleChangePassword,
            goToLogin,
            showLoginButton,
            starsRef,
            starsCount,
        };
    }
};
</script>

<style scoped>
.title {
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
  transform: translate(-50%, 20%);
  width: 750px;
  height: 500px;
  background: rgba(255, 255, 255, 0.2);
  backdrop-filter: blur(10px);
  border-radius: 20px; /* 设置圆角为20像素 */
  /* 其他样式，例如边框、阴影等 */
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); /* 添加轻微的阴影效果 */
}

.input1, .input2, .input3 {
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

.submit_button {
  position: absolute;
  bottom: 20%;
  left: 50%;
  transform: translateX(-50%);
  font-size: 1.5em;
  cursor: pointer;
  width: 30%;
}

.return {
  position: absolute;
  bottom: 10%;
  left: 50%;
  transform: translateX(-50%);
  font-size: 1.5em;
  width:30%;
  cursor: pointer;
}

.return_message1, .return_message2 {
  color: #fefefe;
  font-size: 2em; /* 设置字号大小 */
  margin:1em;
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  text-align: center;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
}

.return_message1 {
  bottom: 10%;
}

.return_message2 {
  bottom: 5%;
}

.change-password-container {
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