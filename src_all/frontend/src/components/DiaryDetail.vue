<template>
    <div class="diary-detail">
        <h1>{{ diary.title }}</h1>
        <p>作者：{{ diary.author }}</p>
        <p>描述对象：{{ diary.description }}</p>
        <p>内容：</p>
        <div v-html="diary.content"></div>
        <p>热度：{{ diary.popularity }}</p>
        <p>评分：{{ diary.rating }}</p>
        <!-- 评分组件 -->
<div class="rating">
            <button
                v-for="rating in ratingOptions"
                :key="rating"
                @click="selectRating(rating)"
                :class="{ 'selected': currentRating === rating }"
            >
                {{ rating }}
            </button>
        </div>
        <button @click="submitRating">提交评分</button>
        <button @click="goBack">返回</button>
    </div>
</template>

<script>
import { ref } from 'vue';
import axios from 'axios';
import { useRoute, useRouter } from 'vue-router';


export default {
    name: "DiaryDetail",

    setup() {
        const route = useRoute();
        const router = useRouter();
        const diary = ref({}); // 存储日记详情

        // 从路由参数中获取日记详情
        const fetchDiaryDetail = async () => {
            const diaryData = JSON.parse(route.query.diary);
            diary.value = diaryData;

            await updatePopularity(diary.value.content);
        };

        //更细日记热度
        const updatePopularity = async (diaryContent) => {
            try {
                const response = await axios.post('/api/diary-popularity', {
                    content: diaryContent
                });
                if (response.data.success) {
                    // 假设后端返回新的热度值
                    diary.value.popularity = response.data.popularity;
                    console.log('热度更新成功');
                } else {
                    console.error('更新热度失败:', response.data.message);
                }
            } catch (err) {
                console.error('更新热度时发生错误:', err);
            }
        };

        // 评分相关数据和方法
        const ratingOptions = [0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5];
        const currentRating = ref(null); // 当前选中的评分

        const selectRating = (rating) => {
            currentRating.value = rating;
        };

        const submitRating = async () => {
            if (currentRating.value === null) {
                console.error('请先选择一个分数');
                return;
            }

            try {
                const response = await axios.post('/api/diary-rating', {
                    content: diary.value.content,
                    rating: currentRating.value,
                });
                if (response.data.success) {
                    alert('评分提交成功'); // 显示成功消息
                    console.log('评分提交成功');
                } else {
                    console.error('评分提交失败:', response.data.message);
                }
            } catch (err) {
                console.error('提交评分时发生错误:', err);
            }
        };

        // 返回按钮
        const goBack = () => {
            router.go(-1); // 返回上一页
        };

        // 初始化获取日记详情
        fetchDiaryDetail();

        return {
            diary,
            goBack,
            ratingOptions,
            currentRating,
            selectRating,
            submitRating,
        };
    },
};
</script>

<style scoped>
.rating button {
    margin: 0 5px;
    padding: 5px 10px;
    border: 1px solid #ddd;
    background-color: #f8f8f8;
    cursor: pointer;
}

.rating button.selected {
    background-color: #e0e0e0;
}
</style>