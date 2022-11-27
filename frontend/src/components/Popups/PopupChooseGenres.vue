<script setup>
import Popup from './Popup.vue';
</script>

<template>
	<Popup>
		<div class="v-popupChooseGenres">
			<div class="v-popupChooseGenres__text">Выберите жанр фильма</div>
			<div class="buttonWrapper">
				<div class="" v-if="types.additional">
					<div class="" v-if="types.additional.genres">
						<v-btn
							v-for="type in types.additional.genres"
							:key="type.id"
							@click="watchFilm(type.id)"
							color="primary"
							class="buttonOfType"
						>
							{{ type.rus_name }}
						</v-btn>
					</div>
				</div>
			</div>
		</div>
	</Popup>
</template>

<script>
import api from '../../mixins/api';
export default {
	components: {
		Popup,
	},
	mixins: [api],
	props: {
		usersId: {
			type: Array,
		},
	},
	data() {
		return {
			types: [],
		};
	},
	methods: {
		// функция отправляет на сервер id пользователей из группы и айди жанра фильма
		watchFilm(id) {
			this.apiPost(``);
		},

		async getGenres() {
			const response = await this.apiPost(`genres/fetch`);
			this.types = response;
		},
	},
	mounted() {
		this.getGenres();
	},
};
</script>

<style>
.v-popupChooseGenres {
	color: black;
	width: 40rem;
	height: 30rem;
	padding: 2rem;
}
.v-popupChooseGenres__text {
	margin-bottom: 2rem;
}
.buttonWrapper {
	display: flex;
	flex-direction: column;
	align-items: stretch;
}
.buttonOfType {
	margin-bottom: 1rem;
}
</style>
