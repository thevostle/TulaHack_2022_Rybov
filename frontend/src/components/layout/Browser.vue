<template>
	<div class="">
		browser.vue
		<br>
		Кнопка 'добавить пользователя' работает. По нажатию кнопки 'смотреть', на сервер уходит массив пользователей из группы для последующей общей рекомендации
	</div>
	
	<!--
	<main class="browser">
		<section class="popular">
      <h2>Популярно сейчас</h2>
      <div class="movieCards popularWrap">
        <div class="movieCard popularMovie">
          <img :src="movieCard.coverSrc" alt="" class="movieCard__cover" />
          <div class="movieCard__ratingBar">{{ movieCard.rating }} %</div>
          <div class="movieCard__footer">
            <span class="movieCard__name">{{ movieCard.name }}</span>
            <span class="movieCard__year">({{ movieCard.year }})</span>
          </div>
        </div>
      </div>
    </section>
		<section class="selected"></section>
	</main>
	-->
</template>

<script>
export default {
	name: 'Broswer',
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
