<!-- StudyTourRecommendations.vue -->
<template>
  <div class="background"></div>
  <form class="form">
    <div class="study-tour-recommendations">
      <h1 class="title">游学推荐</h1>
      <button class="return_button" @click.prevent="goToDashboard">返回首页</button>
      <!-- 筛选选项 -->
      <div class="search">
        <div class="filters">
          <select v-model="filterType">
            <option value="all">全部</option>
            <option value="scenic">景区</option>
            <option value="campus">学校</option>
          </select>
          <select v-model="limit">
            <option value="all">全部</option>
            <option value="10">前十</option>
          </select>
          <select v-model="sort">
            <option value="default">默认排序</option>
            <option value="popularity">热度</option>
            <option value="rating">评分</option>
          </select>
        </div>
        <!-- 搜索框 -->
        <input type="text" v-model="searchKeyword" placeholder="搜索景区或学校">
        <button @click.prevent="search">搜索</button>
      </div>
      <!-- 游学推荐列表 -->
      <ul class="recommendations-list">
        <li v-for="item in recommendations" :key="item.id" class="recommendation-item">
          <p>名称：{{ item.name }}</p>
          <p>热度：{{ item.popularity }} </p>
          <p>评分：{{ item.rating }} </p>
          <!-- 点击跳转到描述页面 -->
          <button @click.prevent="goToDescription">详情</button>
        </li>
      </ul>
    </div>
  </form>
</template>

<script>
import { ref } from 'vue';
import axios from 'axios';
import { useRouter } from 'vue-router';

export default {
  name: 'StudyTourRecommendations',
  setup() {
    const recommendations = ref([]); // 存储后端发来的游学推荐信息
    const filterType = ref('all'); // 筛选类型
    const limit = ref('all'); // 展示数量限制
    const sort = ref('default'); // 排序方式
    const searchKeyword = ref(''); // 搜索关键字
    const router = useRouter(); // vue-router

// 解析后端返回的字符串数据
    const parseRecommendations = (data) => {
      return data.split('\n').filter(line => line.trim() !== '').map(line => {
        const parts = line.split(' '); // 根据空格分割每一行
        return {
          id: parseInt(parts[0], 10), // 将ID转换为数字
          name: parts[1], // 类型
          type: parts[2], // 名称
          popularity: parseInt(parts[3], 10), // 热度转换为数字
          rating: parseFloat(parts[4]), // 评分转换为浮点数
        };
      });
    };

    // 获取游学推荐数据
    const fetchRecommendations = async () => {
      try {
          const bodyData = {
            filterType: filterType.value,
            limit: limit.value,
              sort: sort.value,
            searchKeyword: searchKeyword.value,
          };

        const response = await axios.post('/api/recommendation', bodyData);

        if(response.data.success)
          recommendations.value = parseRecommendations(response.data.list);
      } catch (err) {
        console.error('Error fetching recommendations:', err);
        }
    };

// 新增搜索函数
    const search = () => {
      console.log('搜索关键字:', searchKeyword.value);
      // 可以在这里添加额外的搜索逻辑（如果需要）
      fetchRecommendations(); // 使用当前的筛选条件和搜索关键字获取数据
    };

    // 跳转到描述页面
    const goToDescription = (item) => {
      // 根据item.type的值来决定跳转的路由
  const path = item.type === 'scenic' ? '/description' : '/descriptionsc';
  router.push(path);
      //router.push(`/description`);
    };

// 定义跳转到首页的函数
      const goToDashboard = () => {
        router.push('/dashboard');
      };

    // 初始化获取数据
    fetchRecommendations();

    return {
      recommendations,
      filterType,
      limit,
      sort,
      searchKeyword,
      search,
      goToDescription,
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
  background-image: url('~@/assets/img/background.png');
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
  backdrop-filter: blur(10px);
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
  margin-bottom: 0em;
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

.return_button {
  transform: translate(-50%, -50%);
  position: absolute;
  top: 2em;
  left: 10%;
}

.search {
  text-align: center;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
}

.recommendation-item {
  color: #fefefe;
  margin-bottom: 3em;
}

</style>