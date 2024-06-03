<template>
    <div class="background"></div>
    <form class="form">
        <div class="diary-detail">
            <h1 class="title">{{ diary.title }}</h1>
            <p class="subtitle">{{ diary.author }}</p>
            <p class="subtitle2">描述对象：{{ diary.description }}</p>
            <div class="content" v-html="diary.content"></div>
            <p class="diary_popularity">热度：{{ diary.popularity }}</p>
            <p class="diary_rating">评分：{{ diary.rating }}</p>
            <!-- 评分组件 -->
            <div class="rating">
                <button
                    v-for="rating in ratingOptions"
                    :key="rating"
                    @click.prevent="selectRating(rating)"
                    :class="{ 'selected': currentRating === rating }"
                >
                    {{ rating }}
                </button>
            </div>
            <button class="submit_button" @click.prevent="submitRating">提交评分</button>
            <button class="return_button" @click.prevent="goBack">返回</button>
        </div>
    </form>
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
.background {
  position: absolute;
  width: 100%;
  height: 100%;
  margin: 0;
  padding: 0;
  background-attachment: fixed;
  overflow: hidden;
  background-image: url('~@/assets/img/diarydetail.jpg');
  background-size: cover;
}

.background::before {
  content: "";
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-image: url('~@/assets/img/diarydetail.jpg');
  background-size: cover;
  background-attachment: fixed;
  z-index: -1; /* 确保背景层在内容层之下 */
}

.form {
  position: absolute;
  transform: translate(-50%, 0%);
  padding:2%;
  top: 3%;
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

.subtitle2 {
  color: #fefefe;
  font-size: 1em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  max-width: 80%;
  text-align: center;
  margin-top:0em;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
  margin-bottom:0.5em;
}

.content {
  color: #fefefe;
  font-size: 1.2em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
  margin:1em;
}

.diary_popularity, .diary_rating {
  color: #fefefe;
  font-size: 1.5em; /* 设置字号大小 */
  font-family: 'STKaiti', 'KaiTi', sans-serif; /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
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

.submit_button {
  text-align: center;
  font-size: 1.5em;
  margin-top: 0.5em;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
  display: block;
}

.return_button {
  text-align: center;
  font-size: 1.5em;
  margin-top: 0.5em;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
  display: block;
}

.rating {
  text-align: center;
  font-size: 1.5em;
  margin-top: 0.5em;
  margin-left: auto; /* 左外边距自动 */
  margin-right: auto; /* 右外边距自动 */
  display: block;
}

.rating button.selected {
    background-color: #568ecf;
}

.diary-detail {

}

</style>