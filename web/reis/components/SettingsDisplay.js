app.component('settings-display', {
    props: {
        cat: {
            type: String,
            required: true
        }
    },
    template:
    /*html*/
    `
    <div class="display" v-if="cat == 'wallpaper'"> 
        <wallpaper-settings @change-wallpaper="changeWallpaper" ></wallpaper-settings>
    </div>
    <div class="display" v-else> 
        <img src="./assets/images/under_construction.gif" />
    </div>
    `,
    methods: {
        changeWallpaper(payload) {
            this.$emit('change-wallpaper', payload)
        }
    }
})