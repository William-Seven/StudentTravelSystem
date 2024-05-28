<!-- myDescriptionSc.vue -->
<template>
  <div class="background"></div>
  <form class="form">
    <div class="description">
      <h1 class="title">北京邮电大学</h1>
      <h2 class="subtitle">Beijing University of Posts and Telecommunications</h2>
      <!-- 这里的描述内容是固定的，不需要从外部传入 -->
      <p class="content">北京邮电大学（Beijing University of Posts and Telecommunications），简称北邮，位于北京市，是中华人民共和国教育部直属、工业和信息化部共建的全国重点大学，位列国家“双一流”建设高校、“211工程”、“985工程优势学科创新平台”，为北京高科大学联盟、中国人工智能教育联席会、CDIO工程教育联盟创始成员，入选国家“111计划”、“2011计划”、中国政府奖学金来华留学生接收院校、教育部第一批卓越工程师教育培养计划高校、国家建设高水平大学公派研究生项目、教育部首批“新工科”研究与实践项目、全国首批深化创新创业教育改革示范高校、一流网络安全学院建设示范项目高校、国家大学生文化素质教育基地、全国邮政行业人才培养基地。</p>
      <!-- 可以添加更多固定内容 -->
      <!-- 跳转到路线规划页面的按钮 -->
      <button class="start_button" @click.prevent="goToRoutePlanner">开始路线规划</button>
      <button class="return_button" @click.prevent="goToDashboard">返回首页</button>
    </div>
  </form>
</template>

<script>
import { useRouter } from 'vue-router';

export default {
    name: 'myDescriptionSc',

    setup() {
    const router = useRouter(); // 创建 router 实例

    // 定义跳转到路线规划页面的函数
    const goToRoutePlanner = () => {
      router.push('/route-planning');
      };

      // 定义跳转到首页的函数
      const goToDashboard = () => {
        router.push('/dashboard');
      };

    return {
      goToRoutePlanner, // 将函数暴露给模板
      goToDashboard,
    };
  },
};
</script>

<style scoped>
.background {
  position: absolute;
  width: 100%;
  height: 100%;
  margin: 0;
  padding: 0;
  background-attachment: fixed;
  overflow: hidden;
  background-image: url('~@/assets/img/BUPT.jpg');
  background-size: cover;
}

.background::before {
  content: "";
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-image: url('~@/assets/img/background.png');
  background-size: cover;
  background-attachment: fixed;
  z-index: -1; /* 确保背景层在内容层之下 */
}

.form {
  position: absolute;
  transform: translate(-50%, 0%);
  padding:2%;
  top: 10%;
  left:50%;
  width: 45%;
  min-height: 500px;
  background: rgba(255, 255, 255, 0.2);
  backdrop-filter: blur(3px);
  border-radius: 20px; /* 设置圆角为20像素 */
  /* 其他样式，例如边框、阴影等 */
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); /* 添加轻微的阴影效果 */
}

.title {
  color: #fefefe;
  font-size: 4em; /* 设置字号大小 */
  margin:0%;
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  margin-top: 0vh; 
  text-align: center;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
}

.subtitle {
  color: #fefefe;
  font-size: 2em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  text-align: center;
  margin-top:0em;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
  margin-bottom:0em;
}

.content {
  color: #fefefe;
  font-size: 1.2em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  margin:1em;
}

button {
  justify-content: space-between;
  margin: auto;
  font-size: 1em;
  border: 1px solid #000; /* 边框样式，可以根据需要调整 */
  cursor: pointer; /* 鼠标悬停时显示指针手势 */
  border-radius: 8px; /* 添加圆角 */
}

button:hover {
  background-color: #56cfcf;
}

.start_button {
  text-align: center;
  position: absolute;
  font-size: 1.5em;
  margin-top: 0.5em;
  display: block;
  bottom: 5%;
  left: 50%;
  transform: translateX(-50%);
}

.return_button {
  transform: translate(-50%, -50%);
  position: absolute;
  top: 2em;
  left: 10%;
}
</style>