// Import the functions you need from the SDKs you need
import { initializeApp } from 'firebase/app'
import { getFirestore } from 'firebase/firestore'
import { getAuth } from 'firebase/auth'
import { getStorage } from 'firebase/storage'
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries
// Your web app's Firebase configuration
const firebaseConfig = {
  apiKey: 'AIzaSyAa0eSI-FK56SQPQ4IvMq4B-Ts7OC2qlIk',
  authDomain: 'crib-hunter-984b0.firebaseapp.com',
  projectId: 'crib-hunter-984b0',
  storageBucket: 'crib-hunter-984b0.appspot.com',
  messagingSenderId: '198300248203',
  appId: '1:198300248203:web:669fdf0c23eb4a16aacc8e',
}

// Initialize Firebase
const app = initializeApp(firebaseConfig)
// export const db = getFireStore();
export const auth = getAuth(app)
export const db = getFirestore()
export const storage = getStorage(app)
