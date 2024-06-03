<!-- PlaceQuery.vue -->
<template>
  <div class="background"></div>
  <div v-show="area" class="map-container">
    <img :src="area === 'scenic' ? require('@/assets/map/map.png') : require('@/assets/map/mapsc.png')" alt="Map">
  </div>
  <form class="form">
    <div class="place-query">
      <h1 class="title">场所查询</h1>
      <button class="return_button" @click.prevent="goToDashboard">返回首页</button>
      <button class="scenic_button" @click="toggleArea('scenic')">景区</button>
      <button class="campus_button" @click="toggleArea('campus')">校园</button>
      <div v-if="area">
        <h2 class="subtitle">{{ area === 'scenic' ? '景区场所' : '校园场所' }}</h2>
      </div>
      <!-- 当前位置输入 -->
      <div>
        <label for="currentLocation">当前位置:</label>
        <input type="text" id="currentLocation" v-model="currentLocation" required>
      </div>
      <!-- 查询范围输入 -->
      <div>
        <label for="searchRange">查询范围 (米):</label>
        <!-- 用户可以输入自定义距离 -->
        <input type="number" id="searchRange" v-model.number="searchRange" min="0" required>
      </div>
      <div>
        <!-- 或者使用拖拽条选择距离范围 -->
        <input type="range" v-model.number="searchRange" min="0" max="5000" step="10">
      </div>
      <!-- 场所种类选择 -->
      <div>
        <label for="placeType">场所种类:</label>
        <!-- 新增输入框，允许用户手动输入场所类型 -->
        <input type="text" id="manualPlaceType" v-model="manualPlaceType" placeholder="输入场所类型" @input="updatePlaceType">
        <select id="placeType" v-model="placeType">
          <option value="all">全部</option>
          <option value="卫生间">卫生间</option>
          <option value="餐饮">餐饮</option>
          <option value="商店">商店</option>
          <option value="广播">广播</option>
          <option value="医务室">医务室</option>
          <option value="服务厅">服务厅</option>
          <option value="停车场">停车场</option>
          <option value="快递站">快递站</option>
          <option value="体育场">体育场</option>
          <option value="图书馆">图书馆</option>
          <option value="医院">医院</option>
          <option value="酒店">酒店</option>
          <!-- 添加更多场所种类选项 -->
        </select>
      </div>
      <!-- 搜索按钮 -->
      <button class="search_button" @click.prevent="search">查询</button>
      <!-- 当前位置显示 -->
      <p class="subtitle2" v-if="currentLocationName">当前位置: {{ currentLocationName }}</p>
      <!-- 搜索结果列表 -->
      <ul v-if="searchResults && searchResults.length" class="search-results">
        <li v-for="result in searchResults" :key="result.id" class="result-item">
          <p>编号：{{ result.id }}</p>
          <p>名称：{{ result.name }}</p>
          <p>类型：{{ result.type }}</p>
          <p>距离：{{ result.distance }} 米</p>
          <!-- 添加“路线”按钮 -->
          <button @click.prevent="goToRoutePlanner(result.id)">路线</button>
        </li>
      </ul>
      <p class="error" v-else-if="searchResults && !searchResults.length">没有找到相关场所</p>
    </div>
  </form>
</template>

<script>
import { ref, onMounted } from 'vue';
import axios from 'axios';
import { useRouter } from 'vue-router';

export default {
  name: 'PlaceQuery',
  setup() {
    const currentLocation = ref(''); // 当前位置
    const currentLocationName = ref('');
    const searchRange = ref(500); // 查询范围，默认200米
    const placeType = ref('all'); // 场所种类
    const searchResults = ref([]); // 搜索结果
    const area = ref('scenic');
    const router = useRouter(); // vue-router
    // 新增响应式变量，用于绑定手动输入的场所类型
    const manualPlaceType = ref('');

    const resetFields = () => {
      currentLocation.value = '';
      currentLocationName.value = '';
      searchRange.value = 500;
      placeType.value = 'all';
      searchResults.value = [];
    };

    onMounted(() => {
      resetFields();
    });

    //解析后端返回的JSON数据
    const parseSearchResults = (data) => {
      return data.filter(line => line.trim() !== '').map(line => {
        const parts = line.split(' '); // 根据空格分割每一行
        return {
          id: parts[0],
          name: parts[1], // 类型
          type: parts[2], // 名称
          distance: parseInt(parts[3], 10), // 距离，转换为整数
        };
      });
    };

    // 新增方法，用于在用户输入时更新场所类型
    const updatePlaceType = () => {
      // 如果手动输入了场所类型，则使用手动输入的类型，否则使用下拉框的值
      if (manualPlaceType.value.trim() !== '') {
        placeType.value = manualPlaceType.value.trim();
      } else {
        placeType.value = 'all'; // 如果没有输入，则默认为“全部”
      }
    };

    // 搜索场所
    const search = async () => {
      try {
        const apiUrl = area.value === 'campus' ? '/api/place-querysc' : '/api/place-query';
        const response = await axios.post(apiUrl, {
          currentLocation: currentLocation.value,
          searchRange: searchRange.value,
          placeType: placeType.value,
        });
        if (response.data.success) {
          const listString = response.data.list.split('\n');
          searchResults.value = parseSearchResults(listString.slice(1)); // 假设后端返回的数据是数组格式
          currentLocationName.value = listString[0].trim();
        }
      } catch (err) {
        console.error('Error searching places:', err);
      }
    };

    const toggleArea = (newArea) => {
      area.value = newArea;
      // 可以在这里添加额外的逻辑，比如重置搜索结果
    };

    // 跳转到首页
    const goToDashboard = () => {
      router.push('/dashboard');
    };

    // 新增跳转到路线规划的方法
    const goToRoutePlanner = (endPointId) => {
      // 假设当前位置编号存储在 currentLocation.value 中
      const startPointId = currentLocation.value;
      router.push({
        path: '/route-planning',
        query: {
          startPoint: startPointId,
          endPoint: endPointId,
          area: area.value,
        }
      });
    };

    return {
      currentLocation,
      currentLocationName,
      searchRange,
      placeType,
      searchResults,
      search,
      goToDashboard,
      goToRoutePlanner,
      toggleArea,
      area,
      resetFields,
      manualPlaceType,
      updatePlaceType,
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
  background-image: url('~@/assets/img/queryback.jpg');
  background-size: cover;
}

.background::before {
  content: "";
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-image: url('~@/assets/img/queryback.jpg');
  background-size: cover;
  background-attachment: fixed;
  z-index: -1;
  /* 确保背景层在内容层之下 */
}

.form {
  position: absolute;
  padding: 2%;
  top: 5%;
  left: 2%;
  width: 45%;
  min-height: 500px;
  background: rgba(255, 255, 255, 0.2);
  backdrop-filter: blur(10px);
  border-radius: 20px;
  /* 设置圆角为20像素 */
  /* 其他样式，例如边框、阴影等 */
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
  /* 添加轻微的阴影效果 */
}

.title {
  color: #fefefe;
  font-size: 4em;
  /* 设置字号大小 */
  margin: 0%;
  font-family: 'STKaiti', 'KaiTi', sans-serif;
  /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  margin-top: 0vh;
  text-align: center;
  margin-left: auto;
  /* 左外边距自动 */
  margin-right: auto;
  /* 右外边距自动 */
  margin-bottom: 0.5em;
}

.subtitle,
.subtitle2,
.error {
  color: #fefefe;
  font-size: 2em;
  /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif;
  /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  text-align: center;
  margin-left: auto;
  /* 左外边距自动 */
  margin-right: auto;
  /* 右外边距自动 */
  margin-bottom: 2vh;
}

button {
  justify-content: space-between;
  margin: auto;
  font-size: 1em;
  border: 1px solid #000;
  /* 边框样式，可以根据需要调整 */
  cursor: pointer;
  /* 鼠标悬停时显示指针手势 */
  border-radius: 8px;
  /* 添加圆角 */
}

button:hover {
  background-color: #56cfcf;
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

.return_button {
  transform: translate(-50%, -50%);
  position: absolute;
  top: 2em;
  left: 10%;
}

.search_button {
  text-align: center;
  font-size: 1.5em;
  margin-top: 0.5em;
  margin-left: auto;
  /* 左外边距自动 */
  margin-right: auto;
  /* 右外边距自动 */
  display: block;
}

label {
  font-size: 1.5em;
  color: #fefefe;
}

.result-item {
  color: #fefefe;
  margin-bottom: 3em;
}

input[type="text"],
input[type="number"] {
  height: 1.5em;
  margin-left: 1em;
}

input[type="range"] {
  width: 50%;
}

.map-container {
  position: absolute;
  top: 5%;
  right: 0%;
  width: 50%;
  max-width: 95%;
  /* 确保地图容器的最大宽度不超过页面宽度 */
  height: 95%;
  max-height: 100%;
  /* 确保地图容器的最大高度不超过页面高度 */
  background-color: transparent;
  overflow: auto;
  /* 如果内容超出容器大小，添加滚动条 */
}

.map-container img {
  position: absolute;
  width: 100%;
  height: auto;
  right: 0%;
  max-width: 96%;
  /* 确保图片的最大宽度不超过其容器的宽度 */
  max-height: 96%;
  /* 确保图片的最大高度不超过其容器的高度 */
  object-fit: contain;
  /* 保持图片的宽高比，确保图片完整显示在容器内 */
}
</style>