<script setup>
import api from '../../mixins/api.js';
</script>

<template>
  <main class="browser">
    <section class="popular">
      <h2>Популярно сейчас</h2>
      <div class="movieCards popularWrap">
        <div
          class="movieCard popularMovie"
          v-for="(movie, index) in popularMovies"
          :key="index">
          <img
            :src="movie.coverSrc"
            class="movieCard__cover" />
          <div class="movieCard__ratingBar">{{ movie.rating }} %</div>
          <div class="movieCard__footer">
            <span class="movieCard__name">{{ movie.name }}</span>
            <span class="movieCard__year">({{ movie.year }})</span>
          </div>
        </div>
      </div>
    </section>
    <section class="selected"></section>
  </main>
</template>

<script>
export default {
  mixins: [api],
  data() {
    return {
      popularMovies: [
        {
          name: 'Pulp Fiction',
          year: 1994,
          rating: 83,
          coverSrc: '',
        },
        {
          name: 'Pulp Fiction',
          year: 1994,
          rating: 83,
          coverSrc: '',
        },
        {
          name: 'Pulp Fiction',
          year: 1994,
          rating: 83,
          coverSrc: '',
        },
        {
          name: 'Pulp Fiction',
          year: 1994,
          rating: 83,
          coverSrc: '',
        },
        {
          name: 'Pulp Fiction',
          year: 1994,
          rating: 83,
          coverSrc: '',
        },
      ],
    };
  },
	mounted() {
		this.getMovies();
	},
  methods: {
    async getMovies() {
			this.popularMovies = await this.apiGet('content/fetch');// .additional.movies;
			console.log(this.popularMovies);
		},
  },
};
</script>

<style scoped>
.movieCards {
  display: grid;
  grid-template-columns: repeat(5, 194px);
  grid-template-rows: 340px;

  column-gap: 16px;
}

.movieCard {
  display: flex;
  flex-direction: column;
}

.movieCard__cover {
  width: 194px;
  height: 225px;
  margin-bottom: 24px;

  background: #c0c0c0;
}
</style>
