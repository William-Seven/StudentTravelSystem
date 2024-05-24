<!-- PlaceQuery.vue -->
<template>
    <div class="place-query">
        <h1>场所查询</h1>
        <button @click="goToDashboard">返回首页</button>
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
            <select id="placeType" v-model="placeType">
                <option value="all">全部</option>
                <option value="卫生间">卫生间</option>
                <option value="餐饮">餐饮</option>
                <option value="商店">商店</option>
                <option value="广播">广播</option>
                <option value="医务室">医务室</option>
                <option value="服务厅">服务厅</option>
            </select>
        </div>
        <!-- 搜索按钮 -->
        <button @click="search">查询</button>
        <!-- 当前位置显示 -->
        <p v-if="currentLocationName">当前位置: {{ currentLocationName }}</p>
        <!-- 搜索结果列表 -->
        <ul v-if="searchResults && searchResults.length" class="search-results">
            <li v-for="result in searchResults" :key="result.id" class="result-item">
                <p>编号：{{ result.id }}</p>
                <p>名称：{{ result.name }}</p>
                <p>类型：{{ result.type }}</p>
                <p>距离：{{ result.distance }} 米</p>
                <!-- 添加“路线”按钮 -->
                <button @click="goToRoutePlanner(result.id)">路线</button>
            </li>
        </ul>
        <p v-else-if="searchResults && !searchResults.length">没有找到相关场所</p>
    </div>
</template>

<script>
import { ref } from 'vue';
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
        const router = useRouter(); // vue-router

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

        // 搜索场所
        const search = async () => {
            try {
                const response = await axios.post('/api/place-query', {
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
                    endPoint: endPointId
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
        };
    },
};
</script>