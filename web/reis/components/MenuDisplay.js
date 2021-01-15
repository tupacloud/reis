app.component('menu-display', {
    props: {
        left: {
            type: Number,
            required: true
        },
        top: {
            type: Number,
            required: true
        }
    },
    template: 
    /*html*/
    `
    <div 
        ref="menu"
        class="menu" 
        :style="{ width: size_w + 'px', height: size_h + 'px', 'margin-left': left + 'px', 'margin-top' : top + 'px' }"
        >

        <div class="nav-bar" @mousedown="getPosition"></div>

        <menu-content></menu-content>

    </div>
    `
    ,
    data() {
        return {
            size_w: 200,
            size_h: 500,
        }
    },
    methods: {
        getPosition(event) {
            this.$emit('move-menu', event)
            console.log('ue');
        },
        resize(type) {
            if (type == 'increase') {
            this.size_w += 10
            this.size_h += 10
            }
            else {
                this.size_w -= 10
                this.size_h -= 10
            }
        }
    }
})