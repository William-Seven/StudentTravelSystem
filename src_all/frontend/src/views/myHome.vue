<template>
  <div class="home">
    <h1 class="title">欢迎来到学生游学系统！</h1>
    <h1 class="introduce">该系统旨在为学生提供便捷的游学活动管理功能，包括游学推荐、游学路线规划、场所查询以及游学日记管理等核心功能。通过该系统，学生可以更好地组织和记录自己的游学经历，提开游学活动的效率和体验。</h1>
    <div class="stars" ref="starsRef">
      <div class="star" v-for="(item, index) in starsCount" :key="index"></div>
    </div>
    <!--添加注册按钮-->
    <router-link to="/register">
      <button class="register_button">注册</button>
    </router-link>
    <!-- 直接提供登录按钮 -->
    <router-link to="/login">
      <button class="login_button">登录</button>
    </router-link>
  </div>
</template>

<script>
import { onMounted, ref } from "vue";

export default {
  name: 'myHome',
  setup() {
    let starsRef = ref(null);

    const starsCount = 800; //星星数量
    const distance = 900; //间距

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

    return {
      starsRef,
      starsCount,
    };
  },
};
</script>

<style lang="css" scoped>
.home {
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
/* 添加以下样式以确保h1的margin为0 */
.title {
  color: #fefefe;
  font-size: 4em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  margin-top: 10vh; /* 从视口顶部向下移动20% */
  text-align: center;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
}

.introduce {
  color: beige;
  font-size: 1.2em;
  margin-top: 20px;
  text-align: center;
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 60%;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
}

.register_button {
  justify-content: space-between;
  align-items: center;
  margin: auto;
  position: absolute;
  bottom: 50%; /* 距离底部的距离 */
  left:25%;
  font-size: 2em;
  border: 1px solid #000; /* 边框样式，可以根据需要调整 */
  cursor: pointer; /* 鼠标悬停时显示指针手势 */
  border-radius: 8px; /* 添加圆角 */
}

.login_button {
  justify-content: space-between;
  align-items: center;
  margin: auto;
  position: absolute;
  bottom: 50%; /* 距离底部的距离 */
  right:25%;
  font-size: 2em;
  border: 1px solid #000; /* 边框样式，可以根据需要调整 */
  cursor: pointer; /* 鼠标悬停时显示指针手势 */
  border-radius: 8px; /* 添加圆角 */
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