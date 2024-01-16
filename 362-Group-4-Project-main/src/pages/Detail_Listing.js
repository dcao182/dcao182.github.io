import { useEffect, useState } from 'react'
import { useParams, Link, useNavigate } from 'react-router-dom'
import {
  collection,
  getDocs,
  getDoc,
  query,
  where,
  doc,
  orderBy,
  limit,
  startAfter,
} from 'firebase/firestore'
import { db } from '../firebase.config'
import { toast } from 'react-toastify'
import { useAuth } from '../contexts/AuthContext'
import SearchBox from '../components/SearchBox'
// import { SellListingItem } from "../components/SellListingItem";
// import "../fetchApi/fetchData";
function Detail_Listing({ listing_type }) {
  const { currentUser } = useAuth()
  const [listings, setListings] = useState(null)
  const [loading, setLoading] = useState(false)
  const [type, setType] = useState(listing_type)
  const [fullListings, setFullListings] = useState(null)
  const params = useParams()
  console.log(params.id)
  const [listing, setListing] = useState(null)

  const fetchListings = async () => {
    try {
      const docRef = await doc(db, 'sell_listing', params.id)
      const docSnap = await getDoc(docRef)

      if (docSnap.exists()) {
        setListing(docSnap.data())
        setLoading(true)
        console.log(listing)
      }
      console.log(listing)
    } catch (e) {
      toast.error(e.message)
    }
  }

  useEffect(() => {
    fetchListings()
  }, [])

  return !loading ? (
    <div>
      <h1>Is Loading...</h1>
    </div>
  ) : (
    <>
      <div className='flex md:flex-row flex-col'>
        <div className='flex w-full m-5 flex-col md:flex-row justify-start md:flex-wrap box-border md:basis-1/2'>
          <div className='p-1 bg-white border flex sm:flex-row'>
            <img src={listing.imgUrls[0]} alt='' />
          </div>
          {listing.imgUrls.map((imageUrl, index) => {
            console.log(imageUrl)
            return (
              <div className='p-1 w-1/2 bg-white border flex sm:flex-row'>
                <img src={imageUrl} alt='' />{' '}
              </div>
            )
          })}
        </div>

        <div className='flex-col justify-center p-2 m-2'>
          <div className='m-auto'>
            {' '}
            ${listing.price} | {listing.bedrooms} bd | {listing.bathrooms} ba
            <h1>{listing.fullAddress}</h1>
            <button class='btn btn-primary'>Request A Tour</button>
            <button class='btn btn-outline mx-2'>Contact Agent</button>
          </div>
          <div>
            <div className='mb-4 border-b border-gray-200'>
              <ul
                className='flex flex-wrap -mb-px text-sm font-medium text-center'
                id='myTab'
                data-tabs-toggle='#myTabContent'
                role='tablist'
              >
                <li className='mr-2' role='presentation'>
                  <button
                    className='inline-block p-4 rounded-t-lg border-b-2'
                    id='profile-tab'
                    data-tabs-target='#profile'
                    type='button'
                    role='tab'
                    aria-controls='profile'
                    aria-selected='false'
                  >
                    Overview
                  </button>
                </li>
                <li className='mr-2' role='presentation'>
                  <button
                    className='inline-block p-4 rounded-t-lg border-b-2 border-transparent hover:text-gray-600 hover:border-gray-300 dark:hover:text-gray-300'
                    id='dashboard-tab'
                    data-tabs-target='#dashboard'
                    type='button'
                    role='tab'
                    aria-controls='dashboard'
                    aria-selected='false'
                  >
                    Map
                  </button>
                </li>
                <li className='mr-2' role='presentation'>
                  <button
                    className='inline-block p-4 rounded-t-lg border-b-2 border-transparent hover:text-gray-600 hover:border-gray-300 dark:hover:text-gray-300'
                    id='settings-tab'
                    data-tabs-target='#settings'
                    type='button'
                    role='tab'
                    aria-controls='settings'
                    aria-selected='false'
                  >
                    Nearby School
                  </button>
                </li>
                <li role='presentation'>
                  <button
                    className='inline-block p-4 rounded-t-lg border-b-2 border-transparent hover:text-gray-600 hover:border-gray-300 dark:hover:text-gray-300'
                    id='contacts-tab'
                    data-tabs-target='#contacts'
                    type='button'
                    role='tab'
                    aria-controls='contacts'
                    aria-selected='false'
                  >
                    Contacts
                  </button>
                </li>
              </ul>
            </div>
            <div id='myTabContent'>
              <div
                className='p-4 bg-gray-50 rounded-lg dark:bg-gray-800'
                id='profile'
                role='tabpanel'
                aria-labelledby='profile-tab'
              >
                <p className='text-sm w-96 text-gray-500 dark:text-gray-400'>
                  {' '}
                  {listing.description}
                </p>
              </div>
              <div
                className='hidden p-4 bg-gray-50 rounded-lg dark:bg-gray-800'
                id='dashboard'
                role='tabpanel'
                aria-labelledby='dashboard-tab'
              >
                <p className='text-sm text-gray-500 dark:text-gray-400'>
                  This is some placeholder content the{' '}
                  <strong className='font-medium text-gray-800 dark:text-white'>
                    Dashboard tab's associated content
                  </strong>
                  . Clicking another tab will toggle the visibility of this one
                  for the next. The tab JavaScript swaps classes to control the
                  content visibility and styling.
                </p>
              </div>
              <div
                className='hidden p-4 bg-gray-50 rounded-lg dark:bg-gray-800'
                id='settings'
                role='tabpanel'
                aria-labelledby='settings-tab'
              >
                <p className='text-sm text-gray-500 dark:text-gray-400'>
                  This is some placeholder content the{' '}
                  <strong className='font-medium text-gray-800 dark:text-white'>
                    Settings tab's associated content
                  </strong>
                  . Clicking another tab will toggle the visibility of this one
                  for the next. The tab JavaScript swaps classes to control the
                  content visibility and styling.
                </p>
              </div>
              <div
                className='hidden p-4 bg-gray-50 rounded-lg dark:bg-gray-800'
                id='contacts'
                role='tabpanel'
                aria-labelledby='contacts-tab'
              >
                <p className='text-sm text-gray-500 dark:text-gray-400'>
                  This is some placeholder content the{' '}
                  <strong className='font-medium text-gray-800 dark:text-white'>
                    Contacts tab's associated content
                  </strong>
                  . Clicking another tab will toggle the visibility of this one
                  for the next. The tab JavaScript swaps classes to control the
                  content visibility and styling.
                </p>
              </div>
            </div>
          </div>
        </div>
      </div>
    </>
  )
}
export default Detail_Listing
