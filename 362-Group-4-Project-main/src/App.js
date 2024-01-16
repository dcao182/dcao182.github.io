import AuthContextProvider from './contexts/AuthContext'
import { useAuth } from './contexts/AuthContext'
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom'
import { ToastContainer } from 'react-toastify'
import PrivateRoute from './components/PrivateRoute'
import SignIn from './pages/SignIn'
import SignUp from './pages/SignUp'
import Home from './pages/Home'
import Listing from './pages/Listing'
import NotFound from './pages/NotFound'
import Navbar from './components/layout/Navbar'
import Footer from './components/layout/Footer'
import Profile from './pages/Profile'
import CreateListing from './pages/CreateListing'
import Detail_Listing from './pages/Detail_Listing'
import 'react-toastify/dist/ReactToastify.css'

function App() {
  // Initialize the FirebaseUI Widget using Firebase.
  const { currentUser } = useAuth()

  return (
    <div>
      <AuthContextProvider>
        <Router>
          <div className='flex flex-col justify-between h-screen'>
            <Navbar />
            <main className='container mx-auto px-3 pb-12'>
              <Routes>
                <Route path='/' element={<Home />} />
                <Route path='/sign-in' element={<SignIn />} />
                <Route path='/sign-up' element={<SignUp />} />
                <Route
                  path='/sell_listing'
                  element={<Listing listing_type='sell' />}
                />
                <Route path='/listing/:id' element={<Detail_Listing />} />
                <Route
                  path='/rent_listing'
                  element={<Listing listing_type='rent' />}
                />
                <Route path='profile' element={<PrivateRoute />}>
                  <Route path='/profile' element={<Profile />} />
                </Route>
                <Route path='/create-listing' element={<CreateListing />} />
                <Route path='/*' element={<NotFound />} />
              </Routes>
            </main>
            <Footer></Footer>
          </div>
        </Router>
        <ToastContainer />
      </AuthContextProvider>
    </div>
  )
}

export default App
