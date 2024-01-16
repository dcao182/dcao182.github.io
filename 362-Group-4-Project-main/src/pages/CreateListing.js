import { useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { toast } from 'react-toastify'
import { useAuth } from '../contexts/AuthContext'
import { addDoc, collection, serverTimestamp } from 'firebase/firestore'
import {
  getStorage,
  ref,
  uploadBytesResumable,
  getDownloadURL,
} from 'firebase/storage'
// import { storage } from '../firebase.config'
import { v4 as uuidv4 } from 'uuid'
import { db } from '../firebase.config'

const CreateListing = () => {
  const { currentUser } = useAuth()
  const navigate = useNavigate()
  const { loading, setLoading } = useState(false)

  const [formData, setFormData] = useState({
    description: '',
    type: '',
    address: '',
    appartment: '',
    city: '',
    state: '',
    price: 0,
    zipCode: 0,
    bedrooms: 1,
    bathrooms: 1,
    images: {},
  })

  const {
    description,
    type,
    address,
    appartment,
    city,
    state,
    zipCode,
    price,
    bedrooms,
    bathrooms,
    images,
  } = formData

  formData.user = currentUser.uid

  const submitHandle = async (e) => {
    e.preventDefault()

    const storeImage = async (image) => {
      return new Promise((resolve, reject) => {
        const storage = getStorage()
        const fileName = `${currentUser.uid}-${image.name}-${uuidv4()}`

        const storageRef = ref(storage, 'images/' + fileName)
        const uploadTask = uploadBytesResumable(storageRef, image)

        uploadTask.on(
          'state_changed',
          (snapshot) => {
            const progress =
              (snapshot.bytesTransferred / snapshot.totalBytes) * 100
            console.log('Upload is ' + progress + '% done')
            switch (snapshot.state) {
              case 'paused':
                console.log('Upload is paused')
                break
              case 'running':
                console.log('Upload is running')
                break
            }
          },
          (error) => {
            reject(error)
          },
          () => {
            // Handle successful uploads on complete
            // For instance, get the download URL: https://firebasestorage.googleapis.com/...
            getDownloadURL(uploadTask.snapshot.ref).then((downloadURL) => {
              resolve(downloadURL)
            })
          }
        )
      })
    }

    const imgUrls = await Promise.all(
      [...images].map((image) => storeImage(image))
    ).catch(() => {
      toast.error('Images not uploading')
      return
    })

    console.log(imgUrls)

    const formDataCopy = {
      ...formData,
      imgUrls,
      timestamp: serverTimestamp(),
      fullAddress: `${address} ${appartment}, ${city}, ${state} ${zipCode}`,
    }

    delete formDataCopy.images
    console.log(formDataCopy)

    const docRef = await addDoc(collection(db, 'sell_listing'), formDataCopy)

    console.log(imgUrls)

    toast.success('Listing saved')
    type == 'sell' ? navigate(`/sell_listing`) : navigate(`/rent_listing`)
  }

  const onMutate = (e) => {
    if (!e.target.files) {
      setFormData((prevState) => ({
        ...prevState,
        [e.target.id]: e.target.value,
      }))
    }

    if (e.target.files) {
      setFormData((prevState) => ({
        ...prevState,
        images: e.target.files,
      }))
    }
  }

  return (
    <>
      <div className='container flex flex-col'>
        <div>
          <header>Create A Listing</header>
        </div>
        <main>
          <div className='w-full md:w-96 md:max-w-full mx-auto'>
            <div className='p-6 border border-gray-300 sm:rounded-md'>
              <form onSubmit={submitHandle}>
                <div className='block mb-6'>
                  <label className='mx-5'>
                    <input
                      className='mx-2'
                      type='radio'
                      id='type'
                      value='sell'
                      name='type'
                      onClick={onMutate}
                    />
                    Sell
                  </label>
                  <label className='mx-5'>
                    <input
                      className='mx-2'
                      type='radio'
                      id='type'
                      value='rent'
                      name='type'
                      onClick={onMutate}
                    />
                    Rent
                  </label>
                </div>
                <label htmlFor='Description' className='block mb-6'>
                  Description
                  <textarea
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='text'
                    id='description'
                    value={description}
                    onChange={onMutate}
                  />
                </label>

                <label htmlFor='address' className='block mb-6'>
                  Address
                  <input
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='text'
                    id='address'
                    value={address}
                    onChange={onMutate}
                  />
                </label>

                <label htmlFor='appartment' className='block mb-6'>
                  Appartment
                  <input
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='text'
                    id='appartment'
                    value={appartment}
                    onChange={onMutate}
                  />
                </label>

                <label htmlFor='city' className='block mb-6'>
                  City
                  <input
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='text'
                    id='city'
                    value={city}
                    onChange={onMutate}
                  />
                </label>
                <label htmlFor='state' className='block mb-6'>
                  State
                  <input
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='text'
                    id='state'
                    value={state}
                    onChange={onMutate}
                  />
                </label>

                <label htmlFor='zipCode' className='block mb-6'>
                  Zip Code
                  <input
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='text'
                    id='zipCode'
                    value={zipCode}
                    onChange={onMutate}
                  />
                </label>

                <label htmlFor='price' className='block mb-6'>
                  Price
                  <input
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='number'
                    id='price'
                    value={price}
                    onChange={onMutate}
                    required
                  />
                </label>

                <label htmlFor='price' className='block mb-6'>
                  Bedrooms
                  <input
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='number'
                    id='bedrooms'
                    value={bedrooms}
                    onChange={onMutate}
                    required
                  />
                </label>

                <label htmlFor='price' className='block mb-6'>
                  Bathrooms
                  <input
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='number'
                    id='bathrooms'
                    value={bathrooms}
                    onChange={onMutate}
                    required
                  />
                </label>

                <label htmlFor='images' className='block mb-6'>
                  Images
                  <input
                    className='block w-full mt-1 border-gray-300 rounded-md shadow-sm'
                    type='file'
                    id='images'
                    accept='.jpg, .png, .jpeg'
                    multiple
                    onChange={onMutate}
                    required
                  />
                </label>

                <button type='submit' className='btn btn-primary'>
                  Submit
                </button>
              </form>
            </div>
          </div>
        </main>
      </div>
    </>
  )
}

export default CreateListing
