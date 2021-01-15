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

        <div class="nav-bar">
        <div class="nav-menu" @mousedown="getPosition">
            <div v-if="menu_mode == 'main'"><h5 style="margin: 10px"><b>Menu</b></h5></div>
            <div v-else><a style="margin-left: 20px" v-on:click="eventHandler('main')"><i class="fa fa-angle-left"></i></a></div>
            <button v-if="!collapsed" type="button" v-on:click="collapse" class="nav-button btn btn-dark"><i class="fa fa-arrow-up"></i></button>
            <button v-else type="button" v-on:click="expand" class="nav-button btn btn-dark"><i class="fa fa-arrow-down"></i></button>
        </div>
        </div>
        
        <transition name='collapse'>
            <div class="menu-content" v-if="!collapsed">
                <div v-if="menu_mode == 'main'"><menu-content @menu-click="eventHandler"></menu-content></div>
                <div v-if="menu_mode == 'history'"><menu-history></menu-history></div>
            </div>
        </transition>
    <div>

    
    `
    ,
    data() {
        return {
            size_h: 60,
            size_w: 300,
            menu_mode: 'main',
            collapsed: false
        }
    },
    methods: {
        eventHandler(option) {
            console.log(option)
            this.menu_mode = option
        },
        expand() {
            this.collapsed = false
        },
        collapse() {
            this.collapsed = true
        },
        getPosition(event) {
            this.$emit('move-menu', event)
            console.log(this.$refs.menu.clientHeight);
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
    },
    computed: {}
})