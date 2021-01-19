app.component('wallpaper-settings', {
    data() {
        return {
            wallpapers: [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24]
        }
    },
    template:
    /*html*/
    `
        <div class="image_gallery">
            <div 
                v-on:click="changeWallpaper(i)" 
                class="image-btn" 
                v-for="(wallpaper, i) in wallpapers">
                <img :src="'./assets/images/wpp/' + wallpaper + '.jpg'" width="110" height="90" />
            </div>
        </div>

    `,
    methods: {
        changeWallpaper(index) {
            this.$emit('change-wallpaper', './assets/images/wpp/' + Number(index + 1) + '.jpg')
        }
    }
})