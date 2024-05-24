<!-- StudyTourRecommendations.vue -->
<template>
  <div class="study-tour-recommendations">
    <h1>游学推荐</h1>
    <button @click="goToDashboard">返回首页</button>
    <!-- 筛选选项 -->
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
    <button @click="search">搜索</button>
    <!-- 游学推荐列表 -->
    <ul class="recommendations-list">
      <li v-for="item in recommendations" :key="item.id" class="recommendation-item">
        <p>名称：{{ item.name }}</p>
        <p>热度：{{ item.popularity }} </p>
        <p>评分：{{ item.rating }} </p>
        <!-- 点击跳转到描述页面 -->
        <button @click="goToDescription">详情</button>
      </li>
    </ul>
  </div>
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
    const goToDescription = () => {
      router.push(`/description`);
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