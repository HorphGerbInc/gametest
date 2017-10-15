pipeline {
    agent {label 'Linux'}
    stages {
        stage('Install Pre-Requisites') {
            sh 'sudo apt-get -y install git cmake build-essential libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev mesa-common-dev'  
        }
        stage('Build') {
            steps {
                checkout scm
                sh 'mkdir build; cd build; cmake ..; make'    
            }
        }
    }
}
