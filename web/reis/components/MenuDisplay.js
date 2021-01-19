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
        class="menu noselect" 
        :style="{ width: size_w + 'px', height: size_h + 'px', 'margin-left': left + 'px', 'margin-top' : top + 'px' }"
        >

        <div class="nav-menu">
        <div class="nav-menu" @mousedown="getPosition">
            <div v-if="menu_mode == 'main'"><h5 style="margin: 10px"><b>Menu</b></h5></div>
            <div v-else-if="menu_mode == 'history'"><a style="margin-left: 20px" v-on:click="eventHandler('main')"><i class="fa fa-angle-left"></i></a> <b style="margin-left: 20px">Histórico</b></div>
            <div v-else-if="menu_mode == 'settings'"><a style="margin-left: 20px" v-on:click="eventHandler('main')"><i class="fa fa-angle-left"></i></a> <b style="margin-left: 20px">Configurações</b></div>
            <button v-if="!collapsed" type="button" v-on:click="collapse" class="nav-button btn btn-dark"><i class="fa fa-arrow-up"></i></button>
            <button v-else type="button" v-on:click="expand" class="nav-button btn btn-dark"><i class="fa fa-arrow-down"></i></button>
        </div>
        </div>
        
        <transition name='collapse'>
            <div class="menu-content" v-if="!collapsed">
                <div v-if="menu_mode == 'main'"><menu-content @menu-click="eventHandler" @open-window="openWindow"></menu-content></div>
                <div v-else-if="menu_mode == 'history'"><menu-history @open="openWindow"></menu-history></div>
                <div v-else-if="menu_mode == 'settings'"><menu-settings @open="openWindow"></menu-settings></div>
            </div>
        </transition>
    </div>

    
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
        openWindow(option) {
            
            let window = {
                title: null,
                type: null,
                scale: null
            }

            if (option.type == "history") {
                window = option 
            }
            else if (option.type == "main") {
                window.title = "Tela inicial"
                window.type = "main"    
            }
            else if (option.type == "settings") {
                window = option  
            }


            this.$emit('open-window', window)
        },
        eventHandler(option) {
            this.menu_mode = option
        },
        expand() {
            this.collapsed = false
        },
        collapse() {
            this.collapsed = true
        },
        getPosition(event) {
            let info = {
                event: event,
                object: this.$refs.menu
            }

            this.$emit('move-menu', info)
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