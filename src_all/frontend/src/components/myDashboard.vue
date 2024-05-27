<!-- myDashboard.vue -->
<template>
  <div class="dashboard-container">
    <div class="stars" ref="starsRef">
      <div class="star" v-for="(item, index) in starsCount" :key="index"></div>
    </div>
    <form class="form">
    <h1 class="title">Group.09</h1>
    <h1 class="title">学生游学系统</h1>
      <div class="features">
        <button class="button1" @click="goToStudyTourRecommendations">游学推荐</button>
        <button class="button2" @click="goToRoutePlanning">路线规划</button>
        <button class="button3" @click="goToPlaceSearch">场所查询</button>
        <button class="button4" @click="goToStudyTourDiary">游学日记</button>
      </div>
    </form>
  </div>
</template>

<script>
import { useRouter } from 'vue-router';
import { ref, onMounted } from "vue";

export default {
  name: 'myDashboard',
  setup() {
    const router = useRouter();

    let starsRef = ref(null);

        const starsCount = 800; //星星数量
        const distance = 900; //间距

    const goToStudyTourRecommendations = () => {
      router.push('/study-tour-recommendations');
    };

    const goToRoutePlanning = () => {
      router.push('/route-planning');
    };

    const goToPlaceSearch = () => {
      router.push('/place-query');
    };

    const goToStudyTourDiary = () => {
      router.push('/study-tour-diary');
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
      goToStudyTourRecommendations,
      goToRoutePlanning,
      goToPlaceSearch,
      goToStudyTourDiary,
      starsRef,
      starsCount,
    };
  }
};
</script>

<style scoped>
.title {
  color: #fefefe;
  font-size: 3em; /* 设置字号大小 */
  margin:0%;
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 90%;
  margin-top: 0vh; /* 从视口顶部向下移动20% */
  text-align: center;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
}

.form {
  position: absolute;
  bottom: 50%;
  left: 50%;
  transform: translate(-50%, -20%);
  width: 750px;
  height: 300px;
  background: rgba(255, 255, 255, 0.2);
  backdrop-filter: blur(10px);
  border-radius: 20px; /* 设置圆角为20像素 */
  /* 其他样式，例如边框、阴影等 */
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); /* 添加轻微的阴影效果 */
}

button {
  transform: translate(-50%, -50%);
  justify-content: space-between;
  margin: auto;
  position: absolute;
  font-size: 2em;
  border: 1px solid #000; /* 边框样式，可以根据需要调整 */
  cursor: pointer; /* 鼠标悬停时显示指针手势 */
  border-radius: 8px; /* 添加圆角 */
}

button:hover {
  background-color: #56cfcf;
}

.button1 {
  position: absolute;
  bottom: 30%;
  left: 20%;
}

.button2 {
  position: absolute;
  bottom: 30%;
  left: 80%;
}

.button3 {
  position: absolute;
  bottom: 10%;
  left: 20%;
}

.button4 {
  position: absolute;
  bottom: 10%;
  left: 80%;
}

.dashboard-container {
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

