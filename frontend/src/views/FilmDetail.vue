<script setup>
import api from '../mixins/api';
import Aside from '../components/layout/Aside.vue';
import MovieCard from '../components/blocks/MovieCard.vue';
</script>

<template>
	<div>
		<Aside />
		<div class="movieDetail wrapper">
			<v-card class="mx-auto" max-width="400">
				<v-img class="align-end text-white" height="200" :src="movieImage" cover>
					<v-card-title>{{ movieTitle }}</v-card-title>
				</v-img>

				<v-card-subtitle class="pt-4">Рейтинг: {{ movieRating }}</v-card-subtitle>

				<v-card-text>
					<div>{{ movieDescription }}</div>
				</v-card-text>

				<v-card-actions>
					<v-btn color="orange" @click="nextMovie"> Смотреть </v-btn>
					<v-btn color="blue" @click="watchMovie"> К следующему </v-btn>
				</v-card-actions>

				<v-card-text>
					<div>
						Оцените фильм:
						<input type="text" v-model="userRating" />
					</div>
				</v-card-text>
			</v-card>
		</div>
	</div>
</template>

<script>
export default {
	components: {
		Aside,
	},
	mixins: [api],
	data() {
		return {
            movie: null,
			movieId: -1,
			movieTitle: '',
			movieDescription: '',
			movieRating: 10,
			userRating: 0,
			movieImage: '',
			movieLinkToKinopoisk: '',
		};
	},
	methods: {
		async getUser() {
			this.userId = this.$route.params.userId;
			const userData = await this.apiPost('user/get/by_id', { id: this.userId });
			this.login = userData.additional.login;
		},
		nextMovie() {
			// запрос на следующий фильм
		},
		watchMovie() {
			// запуск стрима
		},
	},
	mounted() {
		this.getUser();
        //this.movie = this.apiGet();
	},
};
</script>
