<!-- RoutePlanner.vue -->
<template>
  <div class="route-planner">
    <h1>路线规划</h1>
    <button @click="goToDashboard">返回首页</button>
    <!-- 选择景区或校园 -->
    <div>
      <button @click="selectArea('scenic')">景区</button>
      <button @click="selectArea('campus')">校园</button>
    </div>
    <!-- 根据选择显示不同的输入框 -->
    <!-- 切换点对点和多途径点 -->
    <div v-if="currentArea">
      <h2>{{ currentArea === 'scenic' ? '景区路线规划' : '校园路线规划' }}</h2>
      <button @click="toggleRouteType">切换到{{ routeType === 'pointToPoint' ? '多途径点' : '点对点' }}</button>
      <!-- 点对点路线规划 -->
      <div v-if="routeType === 'pointToPoint'">
        <input v-model="startPoint" placeholder="起点">
        <input v-model="endPoint" placeholder="终点">
        <select v-model="transport">
          <option value="walk">步行</option>
          <!--景区特有的电动车-->
          <option v-if="currentArea === 'scenic'" value="ebike">电动车</option>
          <!-- 校园的交通工具选项 -->
          <option v-if="currentArea === 'campus'" value="bike">自行车</option>
        </select>
        <button @click="searchRoute">搜索</button>
      </div>
      <!-- 多途径点路线规划 -->
      <div v-else>
        <input v-model="currentLocation" placeholder="当前位置">
        <div v-for="(point, index) in viaPoints" :key="index">
          <input v-model="viaPoints[index]" placeholder="途径点">
        </div>
        <button @click="addViaPoint">添加途径点</button>
        <button @click="searchRoute">搜索</button>
      </div>
    </div>
    <div v-if="error" class="error">{{ error }}</div>
    <div v-if="routeInfo" class="route-info">
      <h3>路线信息:</h3>
      <!-- 使用 v-html 来渲染HTML实体 -->
      <div v-html="routeInfo"></div>
    </div>
  </div>
</template>

<script>
import { ref, onMounted } from 'vue';
import axios from 'axios';
import { useRouter } from 'vue-router';

export default {
  name: 'RoutePlanner',
  setup() {
    const currentArea = ref('scenic');
    const routeType = ref('pointToPoint'); // 默认为点对点路线规划
    const startPoint = ref('');
    const endPoint = ref('');
    const currentLocation = ref('');
    const viaPoints = ref(['']);
    const transport = ref('walk');
    const error = ref('');
    const routeInfo = ref('');
    const router = useRouter();

    // 从路由获取查询参数
    const { query } = router.currentRoute.value;

    // 新增重置字段的函数
    const resetFields = () => {
      startPoint.value = '';
      endPoint.value = '';
      currentLocation.value = '';
      viaPoints.value = ['']; // 重置途径点列表
      transport.value = 'walk'; // 重置交通工具
      error.value = ''; // 清除错误信息
      routeInfo.value = ''; // 清除路线信息
    };

    //onMounted(resetFields); // 组件挂载时重置字段

    onMounted(() => {
      // 组件挂载时重置字段
      resetFields();

      // 设置起点和终点
      if (query.startPoint && query.endPoint) {
        startPoint.value = query.startPoint;
        endPoint.value = query.endPoint;
      }
    });

    const toggleRouteType = () => {
      resetFields(); // 添加重置字段操作
      routeType.value = routeType.value === 'pointToPoint' ? 'multipleWaypoints' : 'pointToPoint';
    };

    const selectArea = (area) => {
      resetFields(); // 添加重置字段操作
      currentArea.value = area;
      //routeType.value = 'pointToPoint'; // 默认选择点对点路线规划
    };

    const addViaPoint = () => {
      viaPoints.value.push('');
    };

    const searchRoute = async () => {
      try {
        const response = await axios.post('/api/route-plan', {
          area: currentArea.value,
          type: routeType.value,
          startPoint: startPoint.value,
          endPoint: endPoint.value,
          currentLocation: currentLocation.value,
          viaPoints: viaPoints.value,
          transport: transport.value,
        });

        if (response.data.success) {
          routeInfo.value = response.data.info;
        } else {
          error.value = response.data.error;
        }
      } catch (err) {
        error.value = '搜索路线时发生错误。';
      }
    };

    // 定义跳转到首页的函数
    const goToDashboard = () => {
      router.push('/dashboard');
    };

    return {
      currentArea,
      routeType,
      startPoint,
      endPoint,
      currentLocation,
      viaPoints,
      transport,
      error,
      routeInfo,
      selectArea,
      addViaPoint,
      searchRoute,
      toggleRouteType,
      resetFields,
      goToDashboard,
    };
  },
};
</script>

<style scoped>
/* 你的 CSS 样式 */
</style>