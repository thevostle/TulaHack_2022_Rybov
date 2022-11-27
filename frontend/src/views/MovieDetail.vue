<script setup>
import api from '../mixins/api.js';
import cookie from '../mixins/cookie.js';
import Aside from '../components/layout/Aside.vue';
</script>

<template>
  <div>
    <Aside />
    <div class="movieDetail wrapper">
      <v-card
        class="mx-auto"
        max-width="400">
        <v-img
          class="align-end text-white"
          :src="poster_url"
          cover>
          <v-card-title>{{ name }}</v-card-title>
        </v-img>

        <v-card-subtitle class="pt-4">Рейтинг: {{ Math.round(rate * 10) / 10 }}</v-card-subtitle>

        <v-card-text>
          <div>{{ description }}</div>
        </v-card-text>

        <v-card-actions>
          <v-btn
            color="orange"
            @click="nextMovie">
            Смотреть
          </v-btn>
          <v-btn
            color="blue"
            @click="watchMovie">
            К следующему
          </v-btn>
        </v-card-actions>

        <v-card-text>
          <div>
            Оцените фильм:
            <input
              type="text"
              v-model="userRate"
							@keypress.enter="rateMovie" />
          </div>
        </v-card-text>
				<v-btn @click="rateMovie">Оценить</v-btn>
      </v-card>
    </div>
  </div>
</template>

<script>
export default {
  components: {
    Aside,
  },
  mixins: [api, cookie],
  data() {
    return {
      movieId: -1,
      name: '',
      poster_url: '',
      rate: 10,
      userRate: 0,
      description: '',
      movieLinkToKinopoisk: '',
			userId: -1,
    };
  },
  methods: {
    // async getUser() {
    //   this.userId = this.$route.params.userId;
    //   const userData = await this.apiPost('user/get/by_id', { id: this.userId });
    //   this.login = userData.additional.login;
    // },
    async getMovie() {
      const movieData = await this.apiPost('content/get', { id: this.movieId });
      for (const prop in movieData.additional) {
        this[prop] = movieData.additional[prop];
      }
    },
    nextMovie() {
      // запрос на следующий фильм
    },
    watchMovie() {
      // запуск стрима
    },
		async rateMovie() {
			const rateData = await this.apiPost(`user/${this.userId}/rates/add`, { movieId: this.movieId, rate: this.userRate });
			console.log(rateData);
		},
  },
  mounted() {
		this.userId = this.getCookie('id');
    this.movieId = this.$route.params.movieId;
    this.getMovie();
  },
};
</script>
