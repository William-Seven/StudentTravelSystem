<!-- myDashboard.vue -->
<template>
  <div class="dashboard-container">
    <h1>Group.09——学生游学系统</h1>
    <div class="features">
      <button @click="goToStudyTourRecommendations">游学推荐</button>
      <button @click="goToRoutePlanning">路线规划</button>
      <button @click="goToPlaceSearch">场所查询</button>
      <button @click="goToStudyTourDiary">游学日记</button>
    </div>
  </div>
</template>

<script>
import { useRouter } from 'vue-router';

export default {
  name: 'myDashboard',
  setup() {
    const router = useRouter();

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

    // 返回响应式引用供模板使用
    return {
      goToStudyTourRecommendations,
      goToRoutePlanning,
      goToPlaceSearch,
      goToStudyTourDiary
    };
  }
};
</script>