var Notification = app.component('notification-display', {
    data() {
        return {
            top: window.innerHeight - 170,
            visible: true        }
    },
    template:
    /*html*/
    `
    <transition name='reversecollapse'>
        <div 
            v-if="visible"
            ref="notif"
            v-on:click="close"
            class="notification"
            :style="{ 'margin-top' : top + 'px' }"
            > 
    
            <slot></slot>

        </div>
    </transition>
    `,
    mounted: function(){
        this.top = this.$el.offsetTop - this.getDeepness(this.$el) * (this.$refs.notif.clientHeight + 10)
    },
    methods: {
        close() {
            this.visible = false
        },
        getDeepness(el) {
            if (el.previousElementSibling.className != "notification") {
                return 0;
            }
            else {
                return this.getDeepness(el.previousElementSibling) + 1;
            }
        }
    }
})