<template>
    <div class="diary-detail">
        <h1>{{ diary.title }}</h1>
        <p>作者：{{ diary.author }}</p>
        <p>描述对象：{{ diary.description }}</p>
        <p>内容：</p>
        <div v-html="diary.content"></div>
        <p>热度：{{ diary.popularity }}</p>
        <p>评分：{{ diary.rating }}</p>
        <button @click="goBack">返回</button>
    </div>
</template>

<script>
import { ref } from 'vue';
import { useRoute, useRouter } from 'vue-router';

export default {
    name: "DiaryDetail",

    setup() {
        const route = useRoute();
        const router = useRouter();
        const diary = ref({}); // 存储日记详情

        // 从路由参数中获取日记详情
        const fetchDiaryDetail = () => {
            const diaryData = JSON.parse(route.query.diary);
            diary.value = diaryData;
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
        };
    },
};
</script>

<style scoped></style>