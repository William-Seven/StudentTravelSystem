<!-- RoutePlanner.vue -->
<template>
  <div class="background"></div>
  <div class="route-planner">
    <form class="form1">
      <h1 class="title">路线规划</h1>
      <button class="return_button" @click="goToDashboard">返回首页</button>
      <!-- 选择景区或校园 -->
      <div>
        <button class="scenic_button" @click.prevent="selectArea('scenic')">景区</button>
        <button class="campus_button" @click.prevent="selectArea('campus')">校园</button>
      </div>
      <!-- 根据选择显示不同的输入框 -->
      <!-- 切换点对点和多途径点 -->
      <div v-if="currentArea">
        <h2 class="subtitle">{{ currentArea === 'scenic' ? '景区路线规划' : '校园路线规划' }}</h2>
        <button class="switch_button" @click.prevent="toggleRouteType">切换到{{ routeType === 'pointToPoint' ? '多途径点' : '点对点' }}</button>
        <button class="search_button" @click.prevent="searchRoute">搜索</button>
        <!-- 点对点路线规划 -->
        <div v-if="routeType === 'pointToPoint'">
          <input class="input_start" v-model="startPoint" placeholder="起点">
          <input class="input_end" v-model="endPoint" placeholder="终点">
          <select v-model="transport">
            <option value="walk">步行</option>
            <!--景区特有的电动车-->
            <option v-if="currentArea === 'scenic'" value="ebike">电动车</option>
            <!-- 校园的交通工具选项 -->
            <option v-if="currentArea === 'campus'" value="bike">自行车</option>
          </select>
          
        </div>
        <!-- 多途径点路线规划 -->
        <div v-else>
          <input class="input_start" v-model="currentLocation" placeholder="当前位置">
          <div v-for="(point, index) in viaPoints" :key="index">
            <input class="input_passing" v-model="viaPoints[index]" placeholder="途径点">
          </div>
          <button class="add_button" @click.prevent="addViaPoint">添加途径点</button>
          
        </div>
      </div>
      <div v-if="error" class="error">{{ error }}</div>
      <div v-if="routeInfo" class="route-info">
        <h3 class="subtitle2">路线信息</h3>
        <!-- 使用 v-html 来渲染HTML实体 -->
        <div class="routeInfo" v-html="routeInfo"></div>
      </div>
    </form>
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

      // 检查URL查询参数中的area
      if (query.area) {
        selectArea(query.area); // 根据查询参数设置当前区域
      }

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
      routeType.value = currentArea.value === 'campus' ? 'pointToPoint' : 'pointToPoint';
      transport.value = currentArea.value === 'campus' ? 'bike' : 'walk';
    };

    const addViaPoint = () => {
      viaPoints.value.push('');
    };

    const searchRoute = async () => {
      try {
        const apiUrl = currentArea.value === 'campus' ? '/api/route-plansc' : '/api/route-plan';
        const response = await axios.post(apiUrl, {
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

.form1 {
  position: absolute;
  padding:2%;
  top: 5%;
  left:2%;
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
  margin-bottom: 0.5em;
}

button {
  justify-content: space-between;
  margin: auto;
  position: absolute;
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
  margin: auto;
}

.scenic_button {
  transform: translate(-50%, -50%);
  position: absolute;
  top: 8em;
  left: 45%;
}

.campus_button {
  transform: translate(-50%, -50%);
  position: absolute;
  top: 8em;
  left: 55%;
}

.search_button, .switch_button {
  position: absolute;
  top: 12em;
}

.search_button {
  left:2.5em;
}

.switch_button {
  left: 6em;
}

.add_button {
  left:2.5em;
}

.subtitle {
  color: #fefefe;
  font-size: 2em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  margin-top:2vh;
  margin-bottom:2vh;
}

.input_start, .input_end, .input_passing {
  color: #000000;
  font-size: 0.5em;
  font-family: 'STKaiti', 'KaiTi', sans-serif;
  position: relative;
  width:25%;
  border-radius: 8px; /* 添加圆角 */
  margin-right: 1em;
}

.input_start, .input_end {
  margin-top: 1em;
}

.input_start, .input_passing {
  margin-left: 1em;
}

.subtitle2, .error{
  color: #fefefe;
  font-size: 2em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  text-align: center;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
  margin-bottom:2vh;
}

.routeInfo {
  color: #fefefe;
  font-size: 1em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  margin-top: 0.5em;
  margin-left: 1em;
  margin-bottom:2vh;
}

</style>